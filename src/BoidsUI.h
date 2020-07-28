///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Frame
///////////////////////////////////////////////////////////////////////////////
class Frame : public wxFrame
{
	private:

	protected:
		wxStaticText* m_numberOfBoidsLabel;
		wxTextCtrl* m_numberOfBoidsText;
		wxStaticText* m_viewDistanceLabel;
		wxTextCtrl* m_viewDistanceText;
		wxStaticText* m_viewAngleLabel;
		wxTextCtrl* m_viewAngleText;
		wxStaticText* m_simulationSpeedLabel;
		wxTextCtrl* m_m_simulationSpeedText;
		wxPanel* m_boidsPanel;

		// Virtual event handlers, overide them in your derived class
		virtual void NumberOfBoidsChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void viewDistanceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void SimulationSpeedChanged( wxCommandEvent& event ) { event.Skip(); }


	public:

		Frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Boids3D"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Frame();

};

