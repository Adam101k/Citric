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

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)  //all properties
{

    // Main panel
    wxPanel* panel_main = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500));
    panel_main->SetBackgroundColour(wxColor(50, 50, 50));

    wxStaticText* text_main = new wxStaticText(panel_main, wxID_ANY, "CITRIC", wxPoint(10, 10)); // Text within the main panel
    text_main->SetForegroundColour(*wxWHITE); // Set text color to white
    text_main->SetBackgroundColour(wxColor(90, 90, 90));

    // Text Adjustments
    wxFont font = text_main->GetFont(); // Font Getter
    font.SetPointSize(17); // Set font size to 16 points
    font.MakeBold(); // Make the font bold
    text_main->SetFont(font); // Apply the font to the static text


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
    panel_top->SetBackgroundColour(wxColor(90, 90, 90)); // Changed color for visibility

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

    // Create two buttons
    wxButton* button_sub2_1 = new wxButton(panel_sub2, wxID_ANY, "Button 1");   // change text for buttons
    wxButton* button_sub2_2 = new wxButton(panel_sub2, wxID_ANY, "Button 2");   // change text for buttons

    // Add the buttons to the vertical sizer
    sizerPanelSub2->Add(button_sub2_1, 0, wxEXPAND | wxALL, 5); // Add button_sub2_1 with border
    sizerPanelSub2->Add(button_sub2_2, 0, wxEXPAND | wxALL, 5); // Add button_sub2_2 with border


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

