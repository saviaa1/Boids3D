///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "BoidsUI.h"

///////////////////////////////////////////////////////////////////////////

Frame::Frame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* BoidsHorizontalSizer;
	BoidsHorizontalSizer = new wxFlexGridSizer( 1, 2, 0, 0 );
	BoidsHorizontalSizer->AddGrowableCol( 1 );
	BoidsHorizontalSizer->AddGrowableRow( 0 );
	BoidsHorizontalSizer->SetFlexibleDirection( wxBOTH );
	BoidsHorizontalSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	wxFlexGridSizer* BoidsControlGrid;
	BoidsControlGrid = new wxFlexGridSizer( 0, 2, 0, 0 );
	BoidsControlGrid->SetFlexibleDirection( wxBOTH );
	BoidsControlGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );

	m_boidsLabel = new wxStaticText( this, wxID_ANY, wxT("Boids"), wxDefaultPosition, wxDefaultSize, 0 );
	m_boidsLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_boidsLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_boidsText = new wxTextCtrl( this, wxID_ANY, wxT("500"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_boidsText, 0, wxALL, 5 );

	m_speedLabel = new wxStaticText( this, wxID_ANY, wxT("Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_speedLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_speedLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_speedText = new wxTextCtrl( this, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_speedText, 0, wxALL, 5 );

	m_worldSizeLabel = new wxStaticText( this, wxID_ANY, wxT("World Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_worldSizeLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_worldSizeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_worldSizeText = new wxTextCtrl( this, wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_worldSizeText, 0, wxALL, 5 );

	m_viewDistanceLabel = new wxStaticText( this, wxID_ANY, wxT("View Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_viewDistanceLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_viewDistanceLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_viewDistanceText = new wxTextCtrl( this, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_viewDistanceText, 0, wxALL, 5 );

	m_viewAngleLabel = new wxStaticText( this, wxID_ANY, wxT("View Angle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_viewAngleLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_viewAngleLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_viewAngleText = new wxTextCtrl( this, wxID_ANY, wxT("90"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_viewAngleText, 0, wxALL, 5 );

	m_alignmentLabel = new wxStaticText( this, wxID_ANY, wxT("Alignment"), wxDefaultPosition, wxDefaultSize, 0 );
	m_alignmentLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_alignmentLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_alignmentText = new wxTextCtrl( this, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_alignmentText, 0, wxALL, 5 );

	m_cohesionLabel = new wxStaticText( this, wxID_ANY, wxT("Cohesion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cohesionLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_cohesionLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_cohesionText = new wxTextCtrl( this, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_cohesionText, 0, wxALL, 5 );

	m_separationLabel = new wxStaticText( this, wxID_ANY, wxT("Separation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_separationLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_separationLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_separationText = new wxTextCtrl( this, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	BoidsControlGrid->Add( m_separationText, 0, wxALL, 5 );

	m_wanderLabel = new wxStaticText( this, wxID_ANY, wxT("Wander"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wanderLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_wanderLabel, 0, wxALL, 5 );

	m_wanderCheck = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_wanderCheck->SetValue(true);
	BoidsControlGrid->Add( m_wanderCheck, 0, wxALL, 5 );

	m_predatorLabel = new wxStaticText( this, wxID_ANY, wxT("Predator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_predatorLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_predatorLabel, 0, wxALL, 5 );

	m_predatorCheck = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_predatorCheck, 0, wxALL, 5 );

	m_realtimeLabel = new wxStaticText( this, wxID_ANY, wxT("Realtime"), wxDefaultPosition, wxDefaultSize, 0 );
	m_realtimeLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_realtimeLabel, 0, wxALL, 5 );

	m_realtimeCheck = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_realtimeCheck->SetValue(true);
	BoidsControlGrid->Add( m_realtimeCheck, 0, wxALL, 5 );


	BoidsHorizontalSizer->Add( BoidsControlGrid, 1, 0, 0 );

	m_boidsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600,600 ), wxTAB_TRAVERSAL );
	BoidsHorizontalSizer->Add( m_boidsPanel, 1, wxEXPAND, 0 );


	this->SetSizer( BoidsHorizontalSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_boidsText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::BoidsFocusChanged ), NULL, this );
	m_boidsText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::BoidsChanged ), NULL, this );
	m_speedText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::SpeedFocusChanged ), NULL, this );
	m_speedText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SpeedChanged ), NULL, this );
	m_worldSizeText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::WorldSizeFocusChanged ), NULL, this );
	m_worldSizeText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::WorldSizeChanged ), NULL, this );
	m_viewDistanceText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::ViewDistanceFocusChanged ), NULL, this );
	m_viewDistanceText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewDistanceChanged ), NULL, this );
	m_viewAngleText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::ViewAngleFocusChanged ), NULL, this );
	m_viewAngleText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewAngleChanged ), NULL, this );
	m_alignmentText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::AlignmentFocusChanged ), NULL, this );
	m_alignmentText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::AlignmentChanged ), NULL, this );
	m_cohesionText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::CohesionFocusChanged ), NULL, this );
	m_cohesionText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::CohesionChanged ), NULL, this );
	m_separationText->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::SeparationFocusChanged ), NULL, this );
	m_separationText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SeparationChanged ), NULL, this );
	m_wanderCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::WanderChanged ), NULL, this );
	m_predatorCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::PredatorChanged ), NULL, this );
	m_realtimeCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::RealtimeChanged ), NULL, this );
}

Frame::~Frame()
{
	// Disconnect Events
	m_boidsText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::BoidsFocusChanged ), NULL, this );
	m_boidsText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::BoidsChanged ), NULL, this );
	m_speedText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::SpeedFocusChanged ), NULL, this );
	m_speedText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SpeedChanged ), NULL, this );
	m_worldSizeText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::WorldSizeFocusChanged ), NULL, this );
	m_worldSizeText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::WorldSizeChanged ), NULL, this );
	m_viewDistanceText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::ViewDistanceFocusChanged ), NULL, this );
	m_viewDistanceText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewDistanceChanged ), NULL, this );
	m_viewAngleText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::ViewAngleFocusChanged ), NULL, this );
	m_viewAngleText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewAngleChanged ), NULL, this );
	m_alignmentText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::AlignmentFocusChanged ), NULL, this );
	m_alignmentText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::AlignmentChanged ), NULL, this );
	m_cohesionText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::CohesionFocusChanged ), NULL, this );
	m_cohesionText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::CohesionChanged ), NULL, this );
	m_separationText->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( Frame::SeparationFocusChanged ), NULL, this );
	m_separationText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SeparationChanged ), NULL, this );
	m_wanderCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::WanderChanged ), NULL, this );
	m_predatorCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::PredatorChanged ), NULL, this );
	m_realtimeCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::RealtimeChanged ), NULL, this );

}
