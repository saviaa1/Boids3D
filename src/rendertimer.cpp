#include "rendertimer.hpp"

RenderTimer::RenderTimer(wxGLCanvas* canvas) : wxTimer() {
    canvas_ = canvas;
}

void RenderTimer::Notify() {
    canvas_->Refresh();
}

void RenderTimer::start() {
    wxTimer::Start(10);
}
