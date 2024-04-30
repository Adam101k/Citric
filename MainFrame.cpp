#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <vector>

//MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title ) {

enum IDS
{
	BUTTON_ID = 2
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(BUTTON_ID, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
//add some controls
//add panel to frame
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxButton* button = new wxButton(panel, wxID_ANY, "FILTERS", wxPoint(650, 10), wxSize(100, 35)); // make BUTTON_ID work
	button->SetForegroundColour(*wxWHITE);
	button->SetBackgroundColour(*wxBLACK);
	//button->SetBackgroundColour(wxColor(169, 169, 169));	
	wxButton* button2 = new wxButton(panel, wxID_ANY, "SELECT", wxPoint(750, 10), wxSize(100, 35));
	button2->SetForegroundColour(*wxWHITE);
	button2->SetBackgroundColour(*wxBLACK);
	wxButton* button3 = new wxButton(panel, wxID_ANY, "FILE SIZE", wxPoint(850, 10), wxSize(100, 35));
	button3->SetForegroundColour(*wxWHITE);
	button3->SetBackgroundColour(*wxBLACK);
	wxButton* button4 = new wxButton(panel, wxID_ANY, "IMPORT", wxPoint(950, 10), wxSize(100, 35));
	button4->SetForegroundColour(*wxWHITE);
	button4->SetBackgroundColour(*wxBLACK);
	wxButton* button5 = new wxButton(panel, wxID_ANY, "LAYERS", wxPoint(1050, 10), wxSize(100, 35));
	button5->SetForegroundColour(*wxWHITE);
	button5->SetBackgroundColour(*wxBLACK);
	wxButton* button6 = new wxButton(panel, wxID_ANY, "MENU", wxPoint(1150, 10), wxSize(100, 35));
	button6->SetForegroundColour(*wxWHITE);
	button6->SetBackgroundColour(*wxBLACK);
//top buttons done			location is good, just move up
	wxButton* button7 = new wxButton(panel, wxID_ANY, "SAVE", wxPoint(40, 590), wxSize(100, 35));
	button7->SetForegroundColour(*wxWHITE);
	button7->SetBackgroundColour(*wxBLACK);
	wxButton* button8 = new wxButton(panel, wxID_ANY, "EXPORT", wxPoint(140, 590), wxSize(100, 35));
	button8->SetForegroundColour(*wxWHITE);
	button8->SetBackgroundColour(*wxBLACK);
	wxButton* button9 = new wxButton(panel, wxID_ANY, "TRASH", wxPoint(240, 590), wxSize(100, 35));
	button9->SetForegroundColour(*wxWHITE);
	button9->SetBackgroundColour(*wxBLACK);
//buttom buttons, could use a horizontal boxsixer
	wxButton* button10 = new wxButton(panel, wxID_ANY, "ERASE", wxPoint(40, 160), wxSize(100, 35));
	button10->SetForegroundColour(*wxWHITE);
	button10->SetBackgroundColour(*wxBLACK);
	wxButton* button11 = new wxButton(panel, wxID_ANY, "BORDER", wxPoint(140, 160), wxSize(100, 35));
	button11->SetForegroundColour(*wxWHITE);
	button11->SetBackgroundColour(*wxBLACK); 	
	wxButton* button12 = new wxButton(panel, wxID_ANY, "CROP", wxPoint(40, 230), wxSize(100, 35));
	button12->SetForegroundColour(*wxWHITE);
	button12->SetBackgroundColour(*wxBLACK);
	wxButton* button13 = new wxButton(panel, wxID_ANY, "GIFS", wxPoint(140, 230), wxSize(100, 35));
	button13->SetForegroundColour(*wxWHITE);
	button13->SetBackgroundColour(*wxBLACK);
	wxButton* button14 = new wxButton(panel, wxID_ANY, "UNDO", wxPoint(40, 300), wxSize(100, 35));
	button14->SetForegroundColour(*wxWHITE);
	button14->SetBackgroundColour(*wxBLACK);
	wxButton* button15 = new wxButton(panel, wxID_ANY, "REDO", wxPoint(140, 300), wxSize(100, 35));
	button15->SetForegroundColour(*wxWHITE);
	button15->SetBackgroundColour(*wxBLACK);
	wxButton* button16 = new wxButton(panel, wxID_ANY, "ROTATE", wxPoint(40, 370), wxSize(100, 35));
	button16->SetForegroundColour(*wxWHITE);
	button16->SetBackgroundColour(*wxBLACK);
	wxButton* button17 = new wxButton(panel, wxID_ANY, "ZOOM", wxPoint(140, 370), wxSize(100, 35));
	button17->SetForegroundColour(*wxWHITE);
	button17->SetBackgroundColour(*wxBLACK);
//tools button menu

	wxStaticText* staticTextTitle = new wxStaticText(panel, wxID_ANY, "C  I  T  R  I  C", wxPoint(100, 10));
	staticTextTitle->SetForegroundColour(*wxWHITE);
	staticTextTitle->SetFont(staticTextTitle->GetFont().Scale(2.1));
	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "TOOLS", wxPoint(120, 130));
	staticText->SetForegroundColour(*wxWHITE);
	wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(1050, 600), wxSize(200, -1)); //lock

	//CreateStatusBar();
	//wxStatusBar* statusbar = new wxStatusBar;
	//statusbar->SetForegroundColour(wxColor(60, 59, 54));


	

}
//events
//implement event handler
void MainFrame::OnButtonClicked(wxCommandEvent& eventtask)
{
	wxLogStatus("Button is clicked");
}