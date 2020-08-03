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

#include "boidcanvas.hpp"
#include "Boids3DFrame.h"
#include "world.hpp"
#include "vector3d.hpp"
#include "boid.hpp"

class MyApp: public wxApp
{
    virtual bool OnInit();
    wxGLCanvas * MyGLCanvas;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	Boids3DFrame *boidsFrame = new Boids3DFrame(nullptr);
    BoidCanvas *glCanvas = new BoidCanvas(boidsFrame);
	glCanvas->glContext = new wxGLContext(glCanvas);
	glCanvas->Reparent(boidsFrame->Get3DPanel());
    int x, y;
    glCanvas->GetParent()->GetSize(&x, &y);
    glCanvas->SetSize(-1, -1, x, y, wxSIZE_USE_EXISTING);
	boidsFrame->Show(true);

	return TRUE;
}
