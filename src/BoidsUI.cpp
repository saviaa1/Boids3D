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
	BoidsHorizontalSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* BoidsControlGrid;
	BoidsControlGrid = new wxFlexGridSizer( 0, 2, 0, 0 );
	BoidsControlGrid->SetFlexibleDirection( wxBOTH );
	BoidsControlGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );

	m_boidsLabel = new wxStaticText( this, wxID_ANY, wxT("Boids"), wxDefaultPosition, wxDefaultSize, 0 );
	m_boidsLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_boidsLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_boidsText = new wxTextCtrl( this, wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_boidsText, 0, wxALL, 5 );

	m_speedLabel = new wxStaticText( this, wxID_ANY, wxT("Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_speedLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_speedLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_speedText = new wxTextCtrl( this, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_speedText, 0, wxALL, 5 );

	m_worldSizeLabel = new wxStaticText( this, wxID_ANY, wxT("World Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_worldSizeLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_worldSizeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_worldSizeText = new wxTextCtrl( this, wxID_ANY, wxT("100.0"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_worldSizeText, 0, wxALL, 5 );

	m_viewDistanceLabel = new wxStaticText( this, wxID_ANY, wxT("View Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_viewDistanceLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_viewDistanceLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_viewDistanceText = new wxTextCtrl( this, wxID_ANY, wxT("10.0"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_viewDistanceText, 0, wxALL, 5 );

	m_viewAngleLabel = new wxStaticText( this, wxID_ANY, wxT("View Angle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_viewAngleLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_viewAngleLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_viewAngleText = new wxTextCtrl( this, wxID_ANY, wxT("220"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_viewAngleText, 0, wxALL, 5 );

	m_alignmentLabel = new wxStaticText( this, wxID_ANY, wxT("Alignment"), wxDefaultPosition, wxDefaultSize, 0 );
	m_alignmentLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_alignmentLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_alignmentText = new wxTextCtrl( this, wxID_ANY, wxT("0.5"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_alignmentText, 0, wxALL, 5 );

	m_cohesionLabel = new wxStaticText( this, wxID_ANY, wxT("Cohesion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cohesionLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_cohesionLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_cohesionText = new wxTextCtrl( this, wxID_ANY, wxT("0.5"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_cohesionText, 0, wxALL, 5 );

	m_separationLabel = new wxStaticText( this, wxID_ANY, wxT("Separation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_separationLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_separationLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_separationText = new wxTextCtrl( this, wxID_ANY, wxT("0.5"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_separationText, 0, wxALL, 5 );

	BoidsHorizontalSizer->Add( BoidsControlGrid, 1, 0, 5 );

	m_boidsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600,600 ), wxTAB_TRAVERSAL );
	BoidsHorizontalSizer->Add( m_boidsPanel, 1, wxALL, 5 );


	this->SetSizer( BoidsHorizontalSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_boidsText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::BoidsChanged ), NULL, this );
	m_speedText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SpeedChanged ), NULL, this );
	m_worldSizeText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::WorldSizeChanged ), NULL, this );
	m_viewDistanceText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewDistanceChanged ), NULL, this );
	m_viewAngleText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewAngleChanged ), NULL, this );
	m_alignmentText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::AlignmentChanged ), NULL, this );
	m_cohesionText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::CohesionChanged ), NULL, this );
	m_separationText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SeparationChanged ), NULL, this );
}

Frame::~Frame()
{
	// Disconnect Events
	m_boidsText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::BoidsChanged ), NULL, this );
	m_speedText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SpeedChanged ), NULL, this );
	m_worldSizeText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::WorldSizeChanged ), NULL, this );
	m_viewDistanceText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewDistanceChanged ), NULL, this );
	m_viewAngleText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::ViewAngleChanged ), NULL, this );
	m_alignmentText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::AlignmentChanged ), NULL, this );
	m_cohesionText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::CohesionChanged ), NULL, this );
	m_separationText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SeparationChanged ), NULL, this );

}
