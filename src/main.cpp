// Standard libraries
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>


// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.
#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <GL/gl.h>
#include <GL/glut.h>

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
                    //Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif

#include "Boids3DFrame.h"
#include "world.hpp"

struct ShaderSources {
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderSources shaderParser(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to complie " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std:: endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

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

class Drawing {
public:
	Drawing(unsigned numBoids = 20) {
		positions_ = new float[4 * 3 * numBoids]; // 4 triangles 3 vertices
		indices_ = new unsigned int[4 * 3 * numBoids];
		boidCount_ = 0;
	}

	float* GetPositions() const {
		return positions_;
	}

	unsigned int* GetIndices() const {
		return indices_;
	}

	unsigned int GetBoidCount() const {
		return boidCount_;
	}

	void addBoid(float x, float y, float z) {
		unsigned int i = boidCount_ * 12;
		unsigned int j = boidCount_ * 4;

		positions_[0 + i] = (-0.5f + x);
		positions_[1 + i] = (-1.0f + y);
		positions_[2 + i] = (0.433f + z);

		positions_[3 + i] = (0.5f + x);
		positions_[4 + i] = (-1.0f + y);
		positions_[5 + i] = (0.433f + z);

		positions_[6 + i] = (0.0f + x);
		positions_[7 + i] = (1.0f + y);
		positions_[8 + i] = (0.0f + z);

		positions_[9 + i] = (0.0f + x);
		positions_[10 + i] = (-1.0f + y);
		positions_[11 + i] = (-0.433f + z);

		indices_[0 + i] = (0 + j);
		indices_[1 + i] = (1 + j);
		indices_[2 + i] = (2 + j);

		indices_[3 + i] = (1 + j);
		indices_[4 + i] = (3 + j);
		indices_[5 + i] = (2 + j);

		indices_[6 + i] = (3 + j);
		indices_[7 + i] = (0 + j);
		indices_[8 + i] = (2 + j);

		indices_[9 + i] = (0 + j);
		indices_[10 + i] = (1 + j);
		indices_[11 + i] = (3 + j);
		boidCount_++;
	}

private:
	float *positions_;
	unsigned int *indices_;
	unsigned int boidCount_;
};

void wxGLCanvasSubClass::Render()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 100.0f);
	glClearDepth(1.0f);
	glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
	glMatrixMode(GL_MODELVIEW);
	
	static const float g_color_buffer_data[] = {
		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  1.0f
	};

	static Drawing d(20);
	d.addBoid(0.0f, 0.0f, -1.0f);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * d.GetBoidCount() * sizeof(float), d.GetPositions(), GL_STATIC_DRAW);

	gluPerspective(45, 1, 1.0f, 100.0f);
	gluLookAt(0, 0, 10, 0, 0,-1, 0, 1, 0);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * d.GetBoidCount() * sizeof(unsigned int), d.GetIndices(), GL_STATIC_DRAW);

	unsigned int colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	ShaderSources source = shaderParser("boid.shader");

	// std::cout << "Vertex" << std::endl;
	// std::cout << source.VertexSource << std::endl;
	// std::cout << "Fragment" << std::endl;
	// std::cout << source.FragmentSource << std::endl;

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	glBindVertexArray(0);

	do {
		//std::cout << "loop" << std::endl;
		glClearColor(0.0, 0.0, 0.4f, 0.0);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glRotatef(1, 0.2f, 0.2f, 0.0f);
		
		glDrawElements(GL_TRIANGLES, (12 * d.GetBoidCount()), GL_UNSIGNED_INT, nullptr);

		glPushMatrix();
        glPopMatrix();
		

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
