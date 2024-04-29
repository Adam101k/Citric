#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <vector>

wxIMPLEMENT_APP(App);


bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("C I T R I C Workspace", wxDefaultPosition, wxDefaultSize);
	mainFrame->SetClientSize(800, 600);
	mainFrame->SetBackgroundColour(*wxBLACK);	
	mainFrame->Center();
	mainFrame->Show(true);
	return true;
}
