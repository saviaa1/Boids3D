#include "boidcanvas.hpp"

BEGIN_EVENT_TABLE(BoidCanvas, wxGLCanvas)
    EVT_PAINT    (BoidCanvas::Paintit)
	EVT_MOUSEWHEEL(BoidCanvas::Zoom)
	EVT_LEFT_DOWN(BoidCanvas::MouseDown)
	EVT_LEFT_UP(BoidCanvas::MouseUp)
	EVT_MOTION(BoidCanvas::MoveCamera)
	EVT_SIZE(BoidCanvas::CanvasResize)
END_EVENT_TABLE()

BoidCanvas::BoidCanvas(wxFrame *parent)
:wxGLCanvas(parent, wxID_ANY, NULL, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"), wxNullPalette){
	boids3dframe_ = (Boids3DFrame *) parent;
	timer = new RenderTimer(this);
	timer->start();	
}

BoidCanvas::~BoidCanvas() {
	delete timer;
}

void BoidCanvas::Paintit(wxPaintEvent& WXUNUSED(event)) {
	int x, y;
    GetParent()->GetSize(&x, &y);
	if (x != width_ || y != height_) {
    	SetSize(-1, -1, x, y, wxSIZE_USE_EXISTING);
		width_ = x;
		height_ = y;
	}
	SetCurrent(*glContext);
	wxPaintDC(this);
	if (!initialized_) {
		auto b3f = (Boids3DFrame *) boids3dframe_;
		HandleArgs(b3f);
		world_ = new World<float>(std::stof(b3f->GetAlignment()),
			std::stof(b3f->GetCohesion()),
			std::stof(b3f->GetSeparation()),
			std::stof(b3f->GetViewDistance()),
			std::stof(b3f->GetSpeed()),
			std::stof(b3f->GetViewAngle()),
			std::stof(b3f->GetWorldSize()),
			std::stof(b3f->GetBoids()));
		b3f->SetWorld(world_);
		InitGL();
	}
    Render();
}

void BoidCanvas::CanvasResize(wxSizeEvent& event) {
	wxSize size = this->GetSize();
	int h = size.GetHeight();
	int w = size.GetWidth();
	glViewport(0, 0, w, h);
	aspect_ratio_ = (float) w / (float) h;
	proj_ = glm::perspective(45.0f, aspect_ratio_, 1.0f, 1500.0f);
	mvp_ = proj_ * view_ * model_;
}

void BoidCanvas::Zoom(wxMouseEvent& event) {
	if (cameraDistance_ - (world_size_ / 25) * event.GetWheelRotation() / event.GetWheelDelta() > 0 &&
		cameraDistance_ - (world_size_ / 25) * event.GetWheelRotation() / event.GetWheelDelta() < world_size_*2) {
		cameraDistance_ -= (world_size_ / 25) * event.GetWheelRotation() / event.GetWheelDelta();
		cam_pos_ = glm::vec3(
			world_size_/2 + (std::cos(rotate_x_) * (std::cos(rotate_y_) * cameraDistance_)),
			world_size_/2 + (std::sin(rotate_y_) * cameraDistance_),
			world_size_/2 + (std::sin(rotate_x_) * (std::cos(rotate_y_) * cameraDistance_))
		);
		//std::cout << "x: " << cam_pos_.x << ", y: " << cam_pos_.y << ", z: " << cam_pos_.z << std::endl;
		view_ = glm::lookAt(
			cam_pos_, // Camera position in the world
			glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // Camera looks at cordinate
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		mvp_ = proj_ * view_ * model_;
	}
}

void BoidCanvas::MouseUp(wxMouseEvent& event) {
	mouse_down_ = false;
	rotate_x_ =+ moving_rotation_x_;
	rotate_y_ =+ moving_rotation_y_;
}

void BoidCanvas::MouseDown(wxMouseEvent& event) {
	mouse_down_ = true;
	const wxPoint pos = wxGetMousePosition();
	rotate_point_x_ = pos.x - this->GetScreenPosition().x;
	rotate_point_y_ = pos.y - this->GetScreenPosition().y;
	//std::cout << rotate_x_ << std::endl;
}

void BoidCanvas::MoveCamera(wxMouseEvent& event) {
	static const float pi = acos(-1.0f);
	if (mouse_down_) {
		float sensitivity = 0.005;
		const wxPoint pos = wxGetMousePosition();
		int mouseX = pos.x - this->GetScreenPosition().x;
		int mouseY = pos.y - this->GetScreenPosition().y;

		moving_rotation_x_ = rotate_x_ + ((mouseX - rotate_point_x_) * sensitivity);
		moving_rotation_y_ = rotate_y_ + ((mouseY - rotate_point_y_) * sensitivity);
		
		if (moving_rotation_y_ > pi / 2 - 0.01) {
			moving_rotation_y_ = pi / 2 - 0.01f;
			const wxPoint pos = wxGetMousePosition();
			rotate_point_y_ = pos.y - this->GetScreenPosition().y;
			rotate_y_ = moving_rotation_y_;
		} else if (moving_rotation_y_ < -pi / 2 + 0.01) {
			moving_rotation_y_ = -pi / 2 + 0.01;
			const wxPoint pos = wxGetMousePosition();
			rotate_point_y_ = pos.y - this->GetScreenPosition().y;
			rotate_y_ = moving_rotation_y_;
		}

		cam_pos_ = glm::vec3(
			world_size_/2 + (std::cos(moving_rotation_x_) * (std::cos(moving_rotation_y_) * cameraDistance_)),
			world_size_/2 + (std::sin(moving_rotation_y_) * cameraDistance_),
			world_size_/2 + (std::sin(moving_rotation_x_) * (std::cos(moving_rotation_y_) * cameraDistance_))
		);

		view_ = glm::lookAt(
			cam_pos_, // Camera position in the world
			glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // Camera looks at cordinate
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		mvp_ = proj_ * view_ * model_;
	}
}

void BoidCanvas::HandleArgs(Boids3DFrame *b3f) {
	int argc = wxTheApp->argc;

	if (argc > 1) b3f->SetBoids(wxTheApp->argv[1]);
	if (argc > 2) b3f->SetSpeed(wxTheApp->argv[2]);
	if (argc > 3) b3f->SetWorldSize(wxTheApp->argv[3]);
	if (argc > 4) b3f->SetViewDistance(wxTheApp->argv[4]);
	if (argc > 5) b3f->SetViewAngle(wxTheApp->argv[5]);
	if (argc > 6) b3f->SetAlignment(wxTheApp->argv[6]);
	if (argc > 7) b3f->SetCohesion(wxTheApp->argv[7]);
	if (argc > 8) b3f->SetSeparation(wxTheApp->argv[8]);
}

void BoidCanvas::InitGL() {
	glutInit(&wxTheApp->argc, wxTheApp->argv);
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		rotate_x_ = M_PI/2;
		wxSize size = this->GetSize();
		int h = size.GetHeight();
		int w = size.GetWidth();
		aspect_ratio_ = (float) w / (float) h;
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 100.0f);
		glClearDepth(1.0f);
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);

		glGenBuffers(1, &buffer_);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), drawing_.GetPositions(), GL_STATIC_DRAW);

		auto b3f = (Boids3DFrame *) boids3dframe_;
		world_size_ = std::stof(b3f->GetWorldSize());
		cam_pos_ = glm::vec3(world_size_/2 + std::cos(rotate_x_) * cameraDistance_, world_size_/2, world_size_/2 + (std::sin(rotate_x_) * cameraDistance_));
		proj_ = glm::perspective(45.0f, aspect_ratio_, 1.0f, world_size_*3);
		view_ = glm::lookAt(
			cam_pos_, // Camera position in the world
			glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // Camera looks at cordinate
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		model_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		mvp_ = proj_ * view_ * model_;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glGenBuffers(1, &ibo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(unsigned int), drawing_.GetIndices(), GL_STATIC_DRAW);

		auto sf = ShaderFactory("boid.shader");

		shader_ = sf.CreateShader();

		sf = ShaderFactory("line.shader");

		line_shader_ = sf.CreateShader();

		glUseProgram(shader_);

		MatrixID_ = glGetUniformLocation(shader_, "u_MVP");

		glUniformMatrix4fv(MatrixID_, 1, GL_FALSE, &mvp_[0][0]);

		glBindVertexArray(0);
		drawing_.SetCubeVertices(world_size_);
		initialized_ = true;
}

glm::quat BoidCanvas::RotationBetweenVectors(vector3d<float> v) {
	glm::vec3 start = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 dest = glm::vec3(v.X(), v.Y(), v.Z());
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;


	if (cosTheta < -1 + 0.001f){
		rotationAxis = cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01)
			rotationAxis = cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);
};

void BoidCanvas::Render()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (world_->GetWorldSizeChanged()) {
		float oldSize = world_size_; 
		world_size_= world_->GetWorldSize();
		drawing_.SetCubeVertices(world_size_);
		cameraDistance_ = cameraDistance_ * (world_size_ / oldSize); 
		cam_pos_ = glm::vec3(
			world_size_/2 + (std::cos(rotate_x_) * (std::cos(rotate_y_) * cameraDistance_)),
			world_size_/2 + (std::sin(rotate_y_) * cameraDistance_),
			world_size_/2 + (std::sin(rotate_x_) * (std::cos(rotate_y_) * cameraDistance_))
		);
		view_ = glm::lookAt(
			cam_pos_, // Camera position in the world
			glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // Camera looks at cordinate
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		proj_ = glm::perspective(45.0f, aspect_ratio_, 1.0f, world_size_*3);
		world_->SetWorldSizeChanged(false);
	}

	auto boids = world_->GetBoids();
	for (auto it : boids) {
		auto vec = it->GetPosition();
		auto rVec = it->GetVelocity();

		glm::quat q = RotationBetweenVectors(rVec);

		glm::mat4 RotationMatrix = glm::toMat4(q);

		model_ = glm::translate(glm::mat4(1.0f), glm::vec3(vec.X(), vec.Y(), vec.Z()));
		model_ = model_ * RotationMatrix;

		glm::mat4 mvp = proj_ * view_ * model_;
		
		glUseProgram(shader_);

		int MatrixID = glGetUniformLocation(shader_, "u_MVP");
		glUniformMatrix4fv(MatrixID_, 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(vao_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
		
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
	}

	mvp_ = proj_ * view_ * glm::mat4(1.0f);

	glUseProgram(line_shader_);

	MatrixID_ = glGetUniformLocation(line_shader_, "u_MVP");

	glUniformMatrix4fv(MatrixID_, 1, GL_FALSE, &mvp_[0][0]);

	glColor3f(0.2, 0.5, 0.4);
    glBegin(GL_LINES);
	float *cubeVertices = drawing_.GetCubeVerticies();
	for (unsigned int i = 0; i < 72; i+=6) {
		glVertex3f(cubeVertices[i], cubeVertices[i+1], cubeVertices[i+2]);
		glVertex3f(cubeVertices[i+3], cubeVertices[i+4], cubeVertices[i+5]);
	}
    glEnd();

	world_->moveBoids();

	glFlush();
	SwapBuffers();
}