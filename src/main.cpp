// Standard libraries
#include <list>
#include <iostream>

// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
                    //Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif

#include "Boids3DFrame.h"

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
    Render();
}

void wxGLCanvasSubClass::Render()
{
	do {
		//std::cout << "loop" << std::endl;
		SetCurrent();
		wxPaintDC(this);
		glClearColor(0.0, 0.0, 0.4f, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
		glMatrixMode(GL_MODELVIEW);
		glRotatef(1, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f,-1.0f,1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f,-1.0f,1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f,2.0f,0.886f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f,-1.0f,1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f,-1.0f,-0.732f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f,2.0f,0.886f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f,-1.0f,-0.732f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f,-1.0f,1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f,2.0f,0.886f);
		glEnd();
		glPushMatrix();
		

		glFlush();
		SwapBuffers();
	} while (true);
}

class MyApp: public wxApp
{
    virtual bool OnInit();
    wxGLCanvas * MyGLCanvas;
};

 
IMPLEMENT_APP(MyApp)
  
bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello GL World"), wxPoint(50,50), wxSize(800,60));
    frame->Show(TRUE);
	Boids3DFrame *boidsFrame = new Boids3DFrame(frame);
	boidsFrame->Show(true);
    wxGLCanvasSubClass *glCanvas = new wxGLCanvasSubClass(boidsFrame);
	glCanvas->Reparent(boidsFrame->Get3DPanel());
    glCanvas->SetSize(-1, -1, 560, 558, wxSIZE_USE_EXISTING);
	glCanvas->SetCurrent();

	return TRUE;
}
