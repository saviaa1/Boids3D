// Standard libraries
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <GL/glew.h>


// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.
#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
                    //Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif

#include "Boids3DFrame.h"
#include "world.hpp"
#include "vector3d.hpp"
#include "boid.hpp"
#include "shader.hpp"
#include "drawing.hpp"

class MyApp: public wxApp
{
    virtual bool OnInit();
    wxGLCanvas * MyGLCanvas;
};

IMPLEMENT_APP(MyApp)

class wxGLCanvasSubClass: public wxGLCanvas {
	void Render();
public:
    wxGLCanvasSubClass(wxFrame* parent);
    void Paintit(wxPaintEvent& event);
	wxGLContext *glContext;
protected:
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
    EVT_PAINT    (wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()

wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent)
:wxGLCanvas(parent, wxID_ANY, NULL, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"), wxNullPalette){
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
}

void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)){
	SetCurrent(*glContext);
	wxPaintDC(this);
	glutInit(&wxGetApp().argc, wxGetApp().argv);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
    Render();
}

void wxGLCanvasSubClass::Render()
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

	do {
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
	} while (true);
}
  
bool MyApp::OnInit()
{
	Boids3DFrame *boidsFrame = new Boids3DFrame(nullptr);
    wxGLCanvasSubClass *glCanvas = new wxGLCanvasSubClass(boidsFrame);
	glCanvas->glContext = new wxGLContext(glCanvas);
	glCanvas->Reparent(boidsFrame->Get3DPanel());
    glCanvas->SetSize(-1, -1, 560, 558, wxSIZE_USE_EXISTING);
	boidsFrame->Show(true);

	return TRUE;
}
