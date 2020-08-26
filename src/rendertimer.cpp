#include "rendertimer.hpp"

RenderTimer::RenderTimer(wxGLCanvas* canvas) : wxTimer() {
    canvas_ = canvas;
}

void RenderTimer::Notify() {
    canvas_->Refresh();
}
