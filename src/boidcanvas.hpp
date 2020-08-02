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

class BoidCanvas: public wxGLCanvas {
	void Render();
public:
    BoidCanvas(wxFrame* parent);
    void Paintit(wxPaintEvent& event);
	wxGLContext *glContext;
protected:
    DECLARE_EVENT_TABLE()
};