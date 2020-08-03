#include "boidcanvas.hpp"

BEGIN_EVENT_TABLE(BoidCanvas, wxGLCanvas)
    EVT_PAINT    (BoidCanvas::Paintit)
END_EVENT_TABLE()

BoidCanvas::BoidCanvas(wxFrame *parent)
:wxGLCanvas(parent, wxID_ANY, NULL, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"), wxNullPalette){
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
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
		glutInit(&wxTheApp->argc, wxTheApp->argv);
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		initialized_ = true;
	}
    Render();
}

void BoidCanvas::Render()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 100.0f);
	glClearDepth(1.0f);
	glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
	glMatrixMode(GL_MODELVIEW);

	static Drawing d;

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), d.GetPositions(), GL_STATIC_DRAW);

	glm::mat4 proj = glm::perspective(45.0f, 1.0f, 1.0f, 100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(0,0,10), // Camera is at (0, 0, 10), in World Space
		glm::vec3(0,0,0), // and looks at the origin
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
	float r = 0.0f;

	//std::cout << "loop" << std::endl;
	glClearColor(0.0, 0.0, 0.4f, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	r += 0.02;

	for (unsigned int i = 0; i < 10; i += 1) {
		float x = (float(rand())/float((RAND_MAX)) * 10.0) - 5.0;
		float y = (float(rand())/float((RAND_MAX)) * 10.0) - 5.0;
		float z = (float(rand())/float((RAND_MAX)) * 10.0) - 5.0;
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
		model = model * glm::rotate(glm::mat4(1.0f), r, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 mvp = proj * view * model;
		
		glUseProgram(shader);

		int MatrixID = glGetUniformLocation(shader, "u_MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
	}

	glFlush();
	SwapBuffers();
}