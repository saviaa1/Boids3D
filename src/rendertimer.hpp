#pragma once

#include <wx/glcanvas.h>
#include <wx/timer.h>

class RenderTimer : public wxTimer {
    wxGLCanvas* canvas_;
public:
    RenderTimer(wxGLCanvas *canvas);
    void Notify();
};
