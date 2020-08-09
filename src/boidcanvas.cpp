#include "boidcanvas.hpp"

BEGIN_EVENT_TABLE(BoidCanvas, wxGLCanvas)
    EVT_PAINT    (BoidCanvas::Paintit)
	EVT_MOUSEWHEEL(BoidCanvas::Zoom)
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

void BoidCanvas::Zoom(wxMouseEvent& event) {
	cameraDistance_ -= 10 * event.GetWheelRotation() / event.GetWheelDelta();
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
		
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 100.0f);
		glClearDepth(1.0f);
		glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
		glMatrixMode(GL_MODELVIEW);
		r_ = 0.0f;
		initialized_ = true;
}

glm::quat RotationBetweenVectors(vector3d<float> v) {
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
	static Drawing d;

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), d.GetPositions(), GL_STATIC_DRAW);

	glm::mat4 proj = glm::perspective(45.0f, 1.0f, 1.0f, 1500.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(50, 50, cameraDistance_), // Camera is at (0, 0, 10), in World Space
		glm::vec3(50,50,-50), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 mvp = proj * view * model;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(unsigned int), d.GetIndices(), GL_STATIC_DRAW);

	static auto sf = ShaderFactory("boid.shader");

	unsigned int shader = sf.CreateShader();

	glUseProgram(shader);

	int MatrixID = glGetUniformLocation(shader, "u_MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(0);
	

	//std::cout << "loop" << std::endl;
	glClearColor(0.0, 0.0, 0.4f, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	r_ += 0.02;
	auto boids = world_->GetBoids();
	for (auto it : boids) {
		auto vec = it->GetPosition();
		auto rVec = it->GetVelocity();
		// auto nVec = rVec.normalize();
		// std::cout << "normalized speed V: " << nVec.X() << ", " << nVec.Y() << ", " << nVec.Z() << std::endl;

		// auto cVec = nVec.crossProduct(modelV);
		// std::cout << "cross product V: " << cVec.X() << ", " << cVec.Y() << ", " << cVec.Z() << std::endl;
		// float a = nVec.angleBetween(modelV);

		glm::quat q = RotationBetweenVectors(rVec);

		glm::mat4 RotationMatrix = glm::toMat4(q);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(vec.X(), vec.Y(), vec.Z()));
		model = model * RotationMatrix;

		glm::mat4 mvp = proj * view * model;

		
		glUseProgram(shader);

		int MatrixID = glGetUniformLocation(shader, "u_MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
	}
	world_->moveBoids();

	glFlush();
	SwapBuffers();
}