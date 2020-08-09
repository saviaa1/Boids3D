#include "Boids3DFrame.h"

Boids3DFrame::Boids3DFrame( wxWindow* parent )
:
Frame( parent )
{

}

void Boids3DFrame::BoidsChanged( wxCommandEvent& event )
{
// TODO: Implement BoidsChanged
}

void Boids3DFrame::SpeedChanged( wxCommandEvent& event )
{
    world_->SetSpeed(std::stof(GetSpeed()));
}

void Boids3DFrame::WorldSizeChanged( wxCommandEvent& event )
{
// TODO: Implement WorldSizeChanged
}

void Boids3DFrame::ViewDistanceChanged( wxCommandEvent& event )
{
    world_->SetViewDistance(std::stof(GetViewDistance()));
}

void Boids3DFrame::ViewAngleChanged( wxCommandEvent& event )
{
    world_->SetViewAngle(std::stof(GetViewAngle()));
}

void Boids3DFrame::AlignmentChanged( wxCommandEvent& event )
{
    world_->SetAligmentWeight(std::stof(GetAlignment()));
}

void Boids3DFrame::CohesionChanged( wxCommandEvent& event )
{
    world_->SetCohesionWeight(std::stof(GetCohesion()));
}

void Boids3DFrame::SeparationChanged( wxCommandEvent& event )
{
    world_->SetSeperationWeight(std::stof(GetSeparation()));
}
