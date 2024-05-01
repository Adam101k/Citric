// Start menu
// Kamilo Ramirez - 4/30/24

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    wxPanel* panel_top;

    void OnResize(wxSizeEvent& event) {
        int width, height;
        GetClientSize(&width, &height); // Get client area size

        // Set the size of the top panel to match the width of the frame
        panel_top->SetSize(0, 0, width, 50);

        // Skip the event to allow default processing
        event.Skip();
    }
};


bool MyApp::OnInit() // function to make frame appear
{
    MyFrame* frame = new MyFrame("Citric", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)  // all properties within the frame
{

    // Main panel instance
    wxPanel* panel_main = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500));
    panel_main->SetBackgroundColour(wxColor(50, 50, 50));

    // Left Panel Instance
    wxPanel* panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_left->SetBackgroundColour(wxColor(70, 70, 70));

    // Middle Panel Instance
    wxPanel* panel_middle = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 600));
    panel_middle->SetBackgroundColour(wxColor(100, 100, 100));

    // Right Panel Instance
    wxPanel* panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    panel_right->SetBackgroundColour(wxColor(70, 70, 70));

    // Top Panel Instance
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1000, 50));
    panel_top->SetBackgroundColour(wxColor(75, 75, 75)); // Changed color for visibility

    // Create centered text for panel_top
    wxStaticText* text_top = new wxStaticText(panel_top, wxID_ANY, "CITRIC", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    text_top->SetForegroundColour(*wxWHITE); // Set text color
    text_top->SetBackgroundColour(wxColour(75, 75, 75)); // Set background color
    // Create the font with larger size and bold
    wxFont font = wxFont(wxFontInfo(22).Bold());
    // Apply the font to the static text control
    text_top->SetFont(font);

    // Create a vertical box sizer for panel_top
    wxBoxSizer* sizerPanelTopText = new wxBoxSizer(wxVERTICAL);
    panel_top->SetSizer(sizerPanelTopText); // Set the sizer for panel_top

    // Add stretchable space to push the text to the center vertically
    sizerPanelTopText->AddStretchSpacer();

    // Add the text to the vertical sizer
    sizerPanelTopText->Add(text_top, 0, wxALIGN_CENTER_HORIZONTAL);

    // Add stretchable space to push the text to the center vertically
    sizerPanelTopText->AddStretchSpacer();

    // Create a horizontal box sizer for the middle panel
    wxBoxSizer* sizerMiddlePanel = new wxBoxSizer(wxHORIZONTAL);
    panel_middle->SetSizer(sizerMiddlePanel); // Set the sizer for the middle panel

    // Create three additional panels for the panel_middle
    wxPanel* panel_sub1 = new wxPanel(panel_middle, wxID_ANY, wxDefaultPosition, wxSize(100, 600));
    panel_sub1->SetBackgroundColour(wxColor(120, 120, 120));

    wxPanel* panel_sub2 = new wxPanel(panel_middle, wxID_ANY, wxDefaultPosition, wxSize(100, 600));
    panel_sub2->SetBackgroundColour(wxColor(120, 120, 120));

    wxPanel* panel_sub3 = new wxPanel(panel_middle, wxID_ANY, wxDefaultPosition, wxSize(100, 600));
    panel_sub3->SetBackgroundColour(wxColor(120, 120, 120));

    // Create a vertical box sizer for panel_sub2
    wxBoxSizer* sizerPanelSub2 = new wxBoxSizer(wxVERTICAL);
    panel_sub2->SetSizer(sizerPanelSub2); // Set the sizer for panel_sub2
    
    // Vertical sub_panel2 panels
    wxPanel* panel_sub2_1 = new wxPanel(panel_sub2, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    panel_sub2_1->SetBackgroundColour(wxColor(120, 120, 120));

    wxPanel* panel_sub2_2 = new wxPanel(panel_sub2, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    panel_sub2_2->SetBackgroundColour(wxColor(120, 120, 120));

    wxPanel* panel_sub2_3 = new wxPanel(panel_sub2, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    panel_sub2_3->SetBackgroundColour(wxColor(120, 120, 120));

    // Create centered text for panel_sub2_1
    wxStaticText* text_sub2_1 = new wxStaticText(panel_sub2_1, wxID_ANY, "WELCOME TO CITRIC", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    text_sub2_1->SetForegroundColour(*wxWHITE); // Set text color
    text_sub2_1->SetBackgroundColour(wxColour(120, 120, 120)); // Set background color

    // Create the font with larger size and bold
    wxFont font1 = wxFont(wxFontInfo(18).Bold());
    // Apply the font to the static text control
    text_sub2_1->SetFont(font1);

    // Create a vertical box sizer for panel_sub2_1
    wxBoxSizer* sizerPanelSub2_1 = new wxBoxSizer(wxVERTICAL);
    panel_sub2_1->SetSizer(sizerPanelSub2_1); // Set the sizer for panel_sub2_1

    // Add a spacer to push the text to the bottom
    sizerPanelSub2_1->AddStretchSpacer();

    // Add the text to the vertical sizer
    sizerPanelSub2_1->Add(text_sub2_1, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5); // Add text_sub2_1 with border at the bottom

    // Add the panels to the vertical sizer
    sizerPanelSub2->Add(panel_sub2_1, 0, wxEXPAND); // Add panel_sub2_1 with border
    sizerPanelSub2->Add(panel_sub2_2, 0, wxEXPAND); // Add panel_sub2_2 with border
    sizerPanelSub2->Add(panel_sub2_3, 0, wxEXPAND); // Add panel_sub2_3 with border

    // Create a button for panel_sub2_2
    wxButton* button_sub2_2 = new wxButton(panel_sub2_2, wxID_ANY, "OPEN WORKSPACE");
    button_sub2_2->SetMinSize(wxSize(80, 30)); // Set minimum size for the button

    // Create a vertical box sizer for panel_sub2_2 for the button
    wxBoxSizer* sizerPanelSub2_2 = new wxBoxSizer(wxVERTICAL);
    panel_sub2_2->SetSizer(sizerPanelSub2_2); // Set the sizer for panel_sub2_2
    // Add the button to the vertical sizer
    sizerPanelSub2_2->Add(button_sub2_2, 0, wxEXPAND | wxALL, 10); // Add button_sub2_2 with border

    // Add the sub panels to the horizontal sizer
    sizerMiddlePanel->Add(panel_sub1, 1, wxEXPAND); // Add panel_sub1 with border
    sizerMiddlePanel->Add(panel_sub2, 1, wxEXPAND); // Add panel_sub2 with border
    sizerMiddlePanel->Add(panel_sub3, 1, wxEXPAND); // Add panel_sub3 with border

    // Create a vertical box sizer for the main panel
    wxBoxSizer* sizerMainPanel = new wxBoxSizer(wxHORIZONTAL);
    sizerMainPanel->AddStretchSpacer(); // Add stretchable space above the text
    sizerMainPanel->AddStretchSpacer(); // Add stretchable space below the text
    panel_main->SetSizer(sizerMainPanel); // Set the sizer for the main panel

    // BoxSizer Main Instance
    wxBoxSizer* sizermain = new wxBoxSizer(wxVERTICAL); // Changed to vertical sizer
    // Add panels to sizermain
    sizermain->Add(panel_top, 0, wxEXPAND); // Added panel_top

    // Horizontal sizer for left, middle, and right panels
    wxBoxSizer* sizerLMR = new wxBoxSizer(wxHORIZONTAL);
    sizerLMR->Add(panel_left, 1, wxEXPAND);
    sizerLMR->Add(panel_middle, 7, wxEXPAND);
    sizerLMR->Add(panel_right, 1, wxEXPAND);

    sizermain->Add(sizerLMR, 1, wxEXPAND);

    SetSizerAndFit(sizermain);

    Layout(); // Forces immediate layout
    Center(); // Centers the frame on the screen

    // Bind the resize event
    Bind(wxEVT_SIZE, &MyFrame::OnResize, this);
}

