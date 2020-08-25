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
#include <wx/checkbox.h>
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
		wxStaticText* m_boidsLabel;
		wxTextCtrl* m_boidsText;
		wxStaticText* m_speedLabel;
		wxTextCtrl* m_speedText;
		wxStaticText* m_worldSizeLabel;
		wxTextCtrl* m_worldSizeText;
		wxStaticText* m_viewDistanceLabel;
		wxTextCtrl* m_viewDistanceText;
		wxStaticText* m_viewAngleLabel;
		wxTextCtrl* m_viewAngleText;
		wxStaticText* m_alignmentLabel;
		wxTextCtrl* m_alignmentText;
		wxStaticText* m_cohesionLabel;
		wxTextCtrl* m_cohesionText;
		wxStaticText* m_separationLabel;
		wxTextCtrl* m_separationText;
		wxStaticText* m_wanderLabel;
		wxCheckBox* m_wanderCheck;
		wxStaticText* m_predatorLabel;
		wxCheckBox* m_predatorCheck;
		wxPanel* m_boidsPanel;

		// Virtual event handlers, overide them in your derived class
		virtual void BoidsFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void BoidsChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void SpeedFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void SpeedChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void WorldSizeFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void WorldSizeChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void ViewDistanceFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void ViewDistanceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void ViewAngleFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void ViewAngleChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void AlignmentFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void AlignmentChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void CohesionFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void CohesionChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void SeparationFocusChanged( wxFocusEvent& event ) { event.Skip(); }
		virtual void SeparationChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void WanderChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void PredatorChanged( wxCommandEvent& event ) { event.Skip(); }


	public:

		Frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Boids3D"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Frame();

};

