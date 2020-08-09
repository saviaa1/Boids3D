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
//		std::cout << x << ", " << y << ", " << z << std::endl;
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(vec.X(), vec.Y(), vec.Z()));
		model = model * glm::rotate(glm::mat4(1.0f), r_, glm::vec3(rVec.X(), rVec.Y(), rVec.Z()));

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