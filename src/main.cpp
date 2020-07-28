// Standard libraries
#include <list>
#include <iostream>

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
protected:
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
    EVT_PAINT    (wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()

wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent)
:wxGLCanvas(parent, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas")){
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
}

void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)){
	SetCurrent();
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
		positions_[2 + i] = (1.288f + z);

		positions_[3 + i] = (0.5f + x);
		positions_[4 + i] = (-1.0f + y);
		positions_[5 + i] = (1.288f + z);

		positions_[6 + i] = (0.0f + x);
		positions_[7 + i] = (1.0f + y);
		positions_[8 + i] = (0.0f + z);

		positions_[9 + i] = (0.0f + x);
		positions_[10 + i] = (-1.0f + y);
		positions_[11 + i] = (0.423f + z);

		indices_[0 + i] = (0 + j);
		indices_[1 + i] = (1 + j);
		indices_[2 + i] = (2 + j);

		indices_[3 + i] = (1 + j);
		indices_[4 + i] = (3 + j);
		indices_[5 + i] = (2 + j);

		indices_[6 + i] = (3 + j);
		indices_[7 + i] = (1 + j);
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
	static Drawing d(20);
	d.addBoid(0.0f, 0.0f, -1.0f);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * d.GetBoidCount() * sizeof(float), d.GetPositions(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * d.GetBoidCount() * sizeof(unsigned int), d.GetIndices(), GL_STATIC_DRAW);
	do {
		//std::cout << "loop" << std::endl;
		
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 100.0f);
		glClearColor(0.0, 0.0, 0.4f, 0.0);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
		glMatrixMode(GL_MODELVIEW);
		glRotatef(1, 0.0f, 0.5f, 1.0f);
		
		glDrawElements(GL_TRIANGLES, (4 * 3 * d.GetBoidCount()), GL_UNSIGNED_INT, nullptr);

		glPushMatrix();
        glPopMatrix();
		

		glFlush();
		SwapBuffers();
	} while (true);
}
  
bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello GL World"), wxPoint(50,50), wxSize(600,600));
    new wxGLCanvasSubClass(frame);

    frame->Show(TRUE);

    return TRUE;
}