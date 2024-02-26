#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/statbmp.h>

// Define a new application type, by deriving from wxApp
class App : public wxApp {
public:
    virtual bool OnInit(); // Override the OnInit method which is called on application start
};

// Define a new frame type: this is going to be our main window
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnImportImage(wxCommandEvent& event); // Event handler for importing images
    wxStaticBitmap* imageDisplay; // Pointer to the control where the image will be displayed

    wxDECLARE_EVENT_TABLE(); // Declare the event table where event handlers are mapped
};

// Map events to handlers: in this case, wxID_OPEN to MainFrame::OnImportImage
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_OPEN, MainFrame::OnImportImage)
wxEND_EVENT_TABLE()

// Implement the main application program
// wxIMPLEMENT_APP(App) macro creates an instance of the application
wxIMPLEMENT_APP(App);

// 'OnInit' function is called when the application starts
bool App::OnInit() {
    // Register the image handlers for PNG, JPEG, and BMP image formats
    wxImage::AddHandler(new wxPNGHandler());
    wxImage::AddHandler(new wxJPEGHandler());
    wxImage::AddHandler(new wxBMPHandler());

    // Get the size of the user's screen
    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    // Set the window size to be 75% of the screen size
    int windowWidth = screenWidth * 0.75;
    int windowHeight = screenHeight * 0.75;

    // Create the main application window with the calculated size
    MainFrame* window = new MainFrame("GUI Test", wxDefaultPosition, wxSize(windowWidth, windowHeight));
    window->Show(true);
    return true;
};


// Constructor for our main frame
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) { // Initialize the wxFrame
    // Create a menu with an 'Import Image' option
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Import Image...\tCtrl-I", "Import an image file");

    // Create a menu bar and add the 'File' menu to it
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar); // Attach the menu bar to the frame

    // Create a sizer for layout management and add an image display control to it
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    sizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 10); // Ensure the control expands to the available space and has a border for aesthetics
    SetSizer(sizer); // Set the sizer as the main sizer for the frame
};

// Event handler for the 'Import Image' menu option
void MainFrame::OnImportImage(wxCommandEvent& event) {
    // Open a file dialog to choose an image file
    wxFileDialog openFileDialog(this, "Open Image file", "", "",
        "Image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // Exit the function if the user cancels the file dialog

    // Load the image from the selected file
    wxImage image(openFileDialog.GetPath(), wxBITMAP_TYPE_ANY);
    if (!image.IsOk()) {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    // Update the image display control with the new image
    imageDisplay->SetBitmap(wxBitmap(image));
    this->Layout(); // Re-calculate the layout of the frame to reflect the new image size
};
