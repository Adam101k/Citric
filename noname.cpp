///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-1-ga36064b9)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"
//#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.hp>
#endif

class MyApp: public wxApp
{
	public:
		virtual bool OnInit();
};

bool MyApp::OnInit()
{
	MyFrame1 *frame = new MyFrame1(NULL,
								   NULL,
								   "CITRIC",
								   wxPoint(50,0) //position of window size
								   wxSize (450, 340),
								   wxDEFAULT_FRAME_STYLE
					
	);
	frame->Show(true);
	return true;
}
void OnOKClick(wxCommandEvent& event)
{
	this->m_textCtrl->SetValue("CITRIC");
	wxString str = this->m_textCtrl->GetValue();
	wxLogMessage(str.mbstr());//bring up menu
}

enum{
	ID_OKButtonClick = 1
};
wxBEGIN_EVENT_TABLE(MyFrame1, wxFrame)
	EVT_MENU(ID_OKButtonClick, MyFrame1::OnOkClick)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);



///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_searchCtrl1 = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_searchCtrl1->ShowSearchButton( true );
	#endif
	m_searchCtrl1->ShowCancelButton( false );
	gbSizer1->Add( m_searchCtrl1, wxGBPosition( 11, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("C I T R I C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("TOOLS"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gbSizer1->Add( m_staticText3, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_toggleBtn14 = new wxToggleButton( m_panel2, wxID_ANY, wxT("FILTERS"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtn14->SetValue( true );
	bSizer2->Add( m_toggleBtn14, 0, wxALL, 5 );

	m_button4 = new wxButton( m_panel2, wxID_ANY, wxT("FILE SIZE"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button4, 0, wxALL, 5 );

	m_button3 = new wxButton( m_panel2, wxID_ANY, wxT("IMPORT"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button3, 0, wxALL, 5 );

	m_button2 = new wxButton( m_panel2, wxID_ANY, wxT("LAYERS"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button2, 0, wxALL, 5 );

	m_button7 = new wxButton( m_panel2, wxID_ANY, wxT("Menu"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button7, 0, wxALL, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 0 );


	m_panel2->SetSizer( bSizer1 );
	m_panel2->Layout();
	bSizer1->Fit( m_panel2 );
	gbSizer1->Add( m_panel2, wxGBPosition( 0, 2 ), wxGBSpan( 11, 6 ), wxEXPAND | wxALL, 0 );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

	m_toggleBtn3 = new wxToggleButton( this, wxID_ANY, wxT("Erase"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_toggleBtn3, 0, wxALL, 5 );

	m_toggleBtn4 = new wxToggleButton( this, wxID_ANY, wxT("BORDER"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_toggleBtn4, 0, wxALL, 5 );

	m_toggleBtn5 = new wxToggleButton( this, wxID_ANY, wxT("CROP"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_toggleBtn5, 0, wxALL, 5 );

	m_toggleBtn6 = new wxToggleButton( this, wxID_ANY, wxT("GIFS"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_toggleBtn6, 0, wxALL, 5 );

	m_toggleBtn7 = new wxToggleButton( this, wxID_ANY, wxT("UNDO"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_toggleBtn7, 0, wxALL, 5 );

	m_toggleBtn8 = new wxToggleButton( this, wxID_ANY, wxT("REDO"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtn8->SetValue( true );
	gSizer1->Add( m_toggleBtn8, 0, wxALL, 5 );

	m_toggleBtn9 = new wxToggleButton( this, wxID_ANY, wxT("ROTATE"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_toggleBtn9, 0, wxALL, 5 );

	m_toggleBtn10 = new wxToggleButton( this, wxID_ANY, wxT("ZOOM"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtn10->SetValue( true );
	gSizer1->Add( m_toggleBtn10, 0, wxALL, 5 );


	gbSizer1->Add( gSizer1, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button4->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::Left click here ), NULL, this );
	m_button3->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::Left click here ), NULL, this );
	m_button2->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::Left click here ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button4->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::Left click here ), NULL, this );
	m_button3->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::Left click here ), NULL, this );
	m_button2->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::Left click here ), NULL, this );

}
