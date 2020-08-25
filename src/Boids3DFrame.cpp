#include "Boids3DFrame.h"

Boids3DFrame::Boids3DFrame( wxWindow* parent )
:
Frame( parent )
{

}

void Boids3DFrame::BoidsFocusChanged( wxFocusEvent& event )
{
    world_->SetNewNumberOfBoids(std::stoi(GetBoids()));
}

void Boids3DFrame::BoidsChanged( wxCommandEvent& event )
{
    world_->SetNewNumberOfBoids(std::stoi(GetBoids()));
}

void Boids3DFrame::SpeedFocusChanged( wxFocusEvent& event )
{
    world_->SetSpeed(std::stof(GetSpeed()));
}

void Boids3DFrame::SpeedChanged( wxCommandEvent& event )
{
    world_->SetSpeed(std::stof(GetSpeed()));
}

void Boids3DFrame::WorldSizeFocusChanged( wxFocusEvent& event )
{
    world_->SetWorldSize(std::stof(GetWorldSize()));
}

void Boids3DFrame::WorldSizeChanged( wxCommandEvent& event )
{
    world_->SetWorldSize(std::stof(GetWorldSize()));
}

void Boids3DFrame::ViewDistanceFocusChanged( wxFocusEvent& event )
{
    world_->SetViewDistance(std::stof(GetViewDistance()));
}

void Boids3DFrame::ViewDistanceChanged( wxCommandEvent& event )
{
    world_->SetViewDistance(std::stof(GetViewDistance()));
}

void Boids3DFrame::ViewAngleFocusChanged( wxFocusEvent& event )
{
    world_->SetViewAngle(std::stof(GetViewAngle()));
}

void Boids3DFrame::ViewAngleChanged( wxCommandEvent& event )
{
    world_->SetViewAngle(std::stof(GetViewAngle()));
}

void Boids3DFrame::AlignmentFocusChanged( wxFocusEvent& event )
{
    world_->SetViewAngle(std::stof(GetViewAngle()));
}

void Boids3DFrame::AlignmentChanged( wxCommandEvent& event )
{
    world_->SetViewAngle(std::stof(GetViewAngle()));
}

void Boids3DFrame::CohesionFocusChanged( wxFocusEvent& event )
{
    world_->SetCohesionWeight(std::stof(GetCohesion()));
}

void Boids3DFrame::CohesionChanged( wxCommandEvent& event )
{
    world_->SetCohesionWeight(std::stof(GetCohesion()));
}

void Boids3DFrame::SeparationFocusChanged( wxFocusEvent& event )
{
    world_->SetSeperationWeight(std::stof(GetSeparation()));
}

void Boids3DFrame::SeparationChanged( wxCommandEvent& event )
{
    world_->SetSeperationWeight(std::stof(GetSeparation()));
}

void Boids3DFrame::WanderChanged( wxCommandEvent& event )
{
    world_->SwitchRandMov();
}

void Boids3DFrame::PredatorChanged( wxCommandEvent& event )
{
// TODO: Implement PredatorChanged
}
