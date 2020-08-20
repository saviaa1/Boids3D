#include "boidcanvas.hpp"

BEGIN_EVENT_TABLE(BoidCanvas, wxGLCanvas)
    EVT_PAINT    (BoidCanvas::Paintit)
	EVT_MOUSEWHEEL(BoidCanvas::Zoom)
	EVT_LEFT_DOWN(BoidCanvas::RotateLeft)
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
			0.5,
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

void BoidCanvas::Zoom(wxMouseEvent& event) {
	if (cameraDistance_ - 10 * event.GetWheelRotation() / event.GetWheelDelta() > 0) {
		cameraDistance_ -= 10 * event.GetWheelRotation() / event.GetWheelDelta();
		cam_pos_ = glm::vec3(world_size_/2 + std::cos(r_) * cameraDistance_, world_size_/2, world_size_/2 + (std::sin(r_) * cameraDistance_));
		std::cout << "x: " << cam_pos_.x << ", y: " << cam_pos_.y << ", z: " << cam_pos_.z << std::endl;
		view_ = glm::lookAt(
			cam_pos_, // Camera is at (0, 0, 10), in World Space
			glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // and looks at the origin
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		mvp_ = proj_ * view_ * model_;
	} else {
		std::cout << "max zoom in" << std::endl;
	}
	
}

void BoidCanvas::RotateLeft(wxMouseEvent& event) {
	r_ += 0.05;
	std::cout << r_ << std::endl;

	cam_pos_ = glm::vec3(world_size_/2 + std::cos(r_) * cameraDistance_, world_size_/2, world_size_/2 + (std::sin(r_) * cameraDistance_));

	std::cout << "x: " << cam_pos_.x << ", y: " << cam_pos_.y << ", z: " << cam_pos_.z << std::endl;
	view_ = glm::lookAt(
		cam_pos_, // Camera is at (0, 0, 10), in World Space+
		glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	mvp_ = proj_ * view_ * model_;
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
		r_ = M_PI/2;
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 100.0f);
		glClearDepth(1.0f);
		glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
		glMatrixMode(GL_MODELVIEW);

		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);

		glGenBuffers(1, &buffer_);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), drawing_.GetPositions(), GL_STATIC_DRAW);

		auto b3f = (Boids3DFrame *) boids3dframe_;
		world_size_ = std::stof(b3f->GetWorldSize());
		cam_pos_ = glm::vec3(world_size_/2 + std::cos(r_) * cameraDistance_, world_size_/2, world_size_/2 + (std::sin(r_) * cameraDistance_));
		std::cout << "x: " << cam_pos_.x << ", y: " << cam_pos_.y << ", z: " << cam_pos_.z << std::endl;
		proj_ = glm::perspective(45.0f, 1.0f, 1.0f, 1500.0f);
		view_ = glm::lookAt(
			cam_pos_, // Camera is at (0, 0, 10), in World Space
			glm::vec3(world_size_/2 ,world_size_/2 ,world_size_/2), // and looks at the origin
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
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
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
	//std::cout << "loop" << std::endl;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto boids = world_->GetBoids();
	for (auto it : boids) {
		auto vec = it->GetPosition();
		auto rVec = it->GetVelocity();
		// auto nVec = rVec.normalize();
		// std::cout << "normalized speed V: " << nVec.X() << ", " << nVec.Y() << ", " << nVec.Z() << std::endl;

		// auto cVec = nVec.crossProduct(modelV);
		// std::cout << "cross product V: " << cVec.X() << ", " << cVec.Y() << ", " << cVec.Z() << std::endl;
		// float a = nVec.angle(modelV);

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