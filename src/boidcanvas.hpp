#pragma once

#include <GL/glew.h>

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/glcanvas.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/common.hpp>


#include "drawing.hpp"
#include "shader.hpp"
#include "rendertimer.hpp"
#include "world.hpp"
#include "Boids3DFrame.h"
#include "vector3d.hpp"

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
    void RotateLeft(wxMouseEvent& event);
    void HandleArgs(Boids3DFrame *b3f);
    glm::quat RotationBetweenVectors(vector3d<float> v);
    void InitGL();
	wxGLContext* glContext;
private:
    glm::mat4 proj_;
    glm::mat4 view_;
    glm::mat4 model_;
    glm::mat4 mvp_;
    unsigned int vao_;
    unsigned int buffer_;
    unsigned int ibo_;
    unsigned int shader_;
    int MatrixID_;
    Drawing drawing_;
    glm::vec3 cam_pos_;
    float r_;
protected:
    DECLARE_EVENT_TABLE()
};
