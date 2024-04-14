#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/statbmp.h>

class MainFrame; // Forward declaration

// Manager class declaration
class Manager {
public:
    Manager(); // Constructor
    void ShowMainFrame(); // Show the main window
    void ImportImage(); // Import image to the workspace
    MainFrame* mainFrame; // Pointer to the main window

private:
    
};

// MainFrame class declaration
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnMenuImportImage(wxCommandEvent& event); // Event handler for the menu to import an image
    void ImportImage(); // Method to handle importing an image without an event
    void UpdateImageDisplay(const wxImage& image); // Update the displayed image

private:
    wxStaticBitmap* imageDisplay; // Pointer to the control where the image will be displayed

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_OPEN, MainFrame::OnMenuImportImage)
wxEND_EVENT_TABLE()

// Manager class implementation
Manager::Manager() {
    // Get the size of the user's screen
    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    // Set the window size to be 75% of the screen size
    int windowWidth = screenWidth * 0.75;
    int windowHeight = screenHeight * 0.75;

    // Create the main application window
    mainFrame = new MainFrame("Image Editor", wxDefaultPosition, wxSize(windowWidth, windowHeight));
}

void Manager::ShowMainFrame() {
    mainFrame->Show(true);
}

void Manager::ImportImage() {
    mainFrame->ImportImage(); // Directly call a method that doesn't need a wxCommandEvent
}

// MainFrame class implementation
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), imageDisplay(nullptr) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Import Image...\tCtrl-I");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    sizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();
}

// MainFrame event handler for the menu
void MainFrame::OnMenuImportImage(wxCommandEvent& event) {
    ImportImage(); // Call the import image method when the menu item is selected
}

// MainFrame method to import an image
void MainFrame::ImportImage() {
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
        "Image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed their mind

    wxImage image(openFileDialog.GetPath(), wxBITMAP_TYPE_ANY);
    if (image.IsOk()) {
        UpdateImageDisplay(image);
    }
    else {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
    }
}

// MainFrame method to update the displayed image
void MainFrame::UpdateImageDisplay(const wxImage& image) {
    imageDisplay->SetBitmap(wxBitmap(image));
    Layout();
    Refresh();
}

// App class implementation
class App : public wxApp {
public:
    bool OnInit() override {
        wxInitAllImageHandlers();

        Manager* manager = new Manager();
        SetTopWindow(manager->mainFrame);
        manager->ShowMainFrame();

        return true;
    }
};

wxIMPLEMENT_APP(App);
