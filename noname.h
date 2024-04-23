///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-1-ga36064b9)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/srchctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/tglbtn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:
		void OnOKClick(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	protected:
		wxButton* m_button1;
		wxTextCtrl* m_textCtrl;

	protected:
		wxSearchCtrl* m_searchCtrl1;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText3;
		wxPanel* m_panel2;
		wxToggleButton* m_toggleBtn14;
		wxButton* m_button4;
		wxButton* m_button3;
		wxButton* m_button2;
		wxButton* m_button7;
		wxToggleButton* m_toggleBtn3;
		wxToggleButton* m_toggleBtn4;
		wxToggleButton* m_toggleBtn5;
		wxToggleButton* m_toggleBtn6;
		wxToggleButton* m_toggleBtn7;
		wxToggleButton* m_toggleBtn8;
		wxToggleButton* m_toggleBtn9;
		wxToggleButton* m_toggleBtn10;

		// Virtual event handlers, override them in your derived class
		virtual void Left click here( wxMouseEvent& event ) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 627,418 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};

