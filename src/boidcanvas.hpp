#pragma once

#include <GL/glew.h>

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/glcanvas.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

#include "drawing.hpp"
#include "shader.hpp"
#include "rendertimer.hpp"
#include "world.hpp"
#include "Boids3DFrame.h"

class BoidCanvas: public wxGLCanvas {
	void Render();
    bool initialized_ = false;
    int width_ = -1;
    int height_ = -1;
    float cameraDistance_ = 200.0f;
    RenderTimer* timer;
    World<float> *world_;
    Boids3DFrame *boids3dframe_;
public:
    BoidCanvas(wxFrame* parent);
    ~BoidCanvas();
    void Paintit(wxPaintEvent& event);
    void Zoom(wxMouseEvent& event);
    void HandleArgs(Boids3DFrame *b3f);
    void InitGL();
	wxGLContext* glContext;
private:
    float r_;
protected:
    DECLARE_EVENT_TABLE()
};