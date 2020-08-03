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

	m_numberOfBoidsLabel = new wxStaticText( this, wxID_ANY, wxT("Number of Boids"), wxDefaultPosition, wxDefaultSize, 0 );
	m_numberOfBoidsLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_numberOfBoidsLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_numberOfBoidsText = new wxTextCtrl( this, wxID_ANY, wxT("1000"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_numberOfBoidsText, 0, wxALL, 5 );

	m_viewDistanceLabel = new wxStaticText( this, wxID_ANY, wxT("View Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_viewDistanceLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_viewDistanceLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_viewDistanceText = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_viewDistanceText, 0, wxALL, 5 );

	m_viewAngleLabel = new wxStaticText( this, wxID_ANY, wxT("View Angle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_viewAngleLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_viewAngleLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_viewAngleText = new wxTextCtrl( this, wxID_ANY, wxT("220"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_viewAngleText, 0, wxALL, 5 );

	m_simulationSpeedLabel = new wxStaticText( this, wxID_ANY, wxT("Simulation Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_simulationSpeedLabel->Wrap( -1 );
	BoidsControlGrid->Add( m_simulationSpeedLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_m_simulationSpeedText = new wxTextCtrl( this, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	BoidsControlGrid->Add( m_m_simulationSpeedText, 0, wxALL, 5 );


	BoidsHorizontalSizer->Add( BoidsControlGrid, 1, 0, 5 );

	m_boidsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600,600 ), wxTAB_TRAVERSAL );
	BoidsHorizontalSizer->Add( m_boidsPanel, 1, wxEXPAND, 5 );


	this->SetSizer( BoidsHorizontalSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_numberOfBoidsText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::NumberOfBoidsChanged ), NULL, this );
	m_viewDistanceText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::viewDistanceChanged ), NULL, this );
	m_m_simulationSpeedText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SimulationSpeedChanged ), NULL, this );
}

Frame::~Frame()
{
	// Disconnect Events
	m_numberOfBoidsText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::NumberOfBoidsChanged ), NULL, this );
	m_viewDistanceText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::viewDistanceChanged ), NULL, this );
	m_m_simulationSpeedText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( Frame::SimulationSpeedChanged ), NULL, this );

}
