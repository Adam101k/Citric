#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/statbmp.h>
#include <wx/animate.h>

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
    void OnMouseWheel(wxMouseEvent& event); // Event handler for mouse wheel
    void ImportImage(); // Method to handle importing an image without an event
    void ImportGifImage(const wxString& path);  // New method for GIFs
    void UpdateImageDisplay(const wxImage& image); // Update the displayed image
    void ClearPreviousDisplay(); // Helper method to clear any existing displays

private:
    wxStaticBitmap* imageDisplay; // Pointer to the control where the image will be displayed
    wxAnimationCtrl* animationCtrl; // Control for displaying animated GIFs

    // Stuff for zooming in and out
    wxImage originalImage;
    double zoomFactor = 1.0;  // Start with no zoom

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_OPEN, MainFrame::OnMenuImportImage)
EVT_MOUSEWHEEL(MainFrame::OnMouseWheel)
wxEND_EVENT_TABLE()

// MainFrame class implementation
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), imageDisplay(nullptr), animationCtrl(nullptr) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Import Image...\tCtrl-I");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddStretchSpacer(1); // Add a spacer that expands

    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    sizer->Add(imageDisplay, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    sizer->AddStretchSpacer(1); // Add another spacer that expands
    SetSizer(sizer);

    Centre();
}

void MainFrame::OnMenuImportImage(wxCommandEvent& event) {
    ImportImage();
}

void MainFrame::OnMouseWheel(wxMouseEvent& event) {
    if (!originalImage.IsOk()) {
        // Ensure the originalImage is loaded when the image is first initialized
        originalImage = imageDisplay->GetBitmap().ConvertToImage();
    }

    int rotation = event.GetWheelRotation();
    // Adjust zoom factor: increase or decrease based on the wheel rotation
    if (rotation > 0) {
        zoomFactor *= 1.1;  // Zoom in
    }
    else {
        zoomFactor *= 0.9;  // Zoom out
    }

    if (imageDisplay && imageDisplay->GetBitmap().IsOk()) {
        // Apply cumulative zoom factor to the original size to calculate the new size
        wxSize originalSize = originalImage.GetSize();
        wxSize newSize(
            static_cast<int>(originalSize.x * zoomFactor),
            static_cast<int>(originalSize.y * zoomFactor)
        );

        // Avoid zooming to zero or a negative size
        if (newSize.x > 0 && newSize.y > 0) {
            // Scale the original image to the new size based on the current zoom factor
            wxImage scaledImage = originalImage.Scale(newSize.x, newSize.y, wxIMAGE_QUALITY_HIGH);

            // Update the display with the new bitmap
            imageDisplay->SetBitmap(wxBitmap(scaledImage));
            Layout();
            Refresh();
        }
    }
}

void MainFrame::ImportImage() {
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
        "Image files (*.bmp;*.png;*.jpg;*.gif)|*.bmp;*.png;*.jpg;*.gif", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // User cancelled

    wxString path = openFileDialog.GetPath();
    wxImage image(path, wxBITMAP_TYPE_ANY);
    if (!image.IsOk()) {
        wxLogError("Cannot open file '%s'.", path);
        return;
    }

    ClearPreviousDisplay(); // Clear any existing content

    if (path.EndsWith(".gif")) {
        ImportGifImage(path);
    }
    else {
        originalImage = image;
        UpdateImageDisplay(image);
    }
}

void MainFrame::ImportGifImage(const wxString& path) {
    wxAnimation animation;
    if (!animation.LoadFile(path)) {
        wxLogError("Failed to load GIF file.");
        return;
    }

    ClearPreviousDisplay(); // Ensure previous displays are cleared

    if (animation.GetFrameCount() > 1) {
        animationCtrl = new wxAnimationCtrl(this, wxID_ANY);
        animationCtrl->SetAnimation(animation);
        animationCtrl->Play();
        animationCtrl->Show();
        GetSizer()->Insert(1, animationCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5); // Center the control
    }
    else {
        wxImage frameImage = animation.GetFrame(0);
        UpdateImageDisplay(frameImage);
    }
    Layout();
    Refresh();
}

void MainFrame::UpdateImageDisplay(const wxImage& image) {
    if (!imageDisplay)
        imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    wxImage scaledImage = image.Scale(image.GetWidth(), image.GetHeight(), wxIMAGE_QUALITY_HIGH);
    imageDisplay->SetBitmap(wxBitmap(scaledImage));
    imageDisplay->Show();
    if (animationCtrl) animationCtrl->Hide();
    Layout();
    Refresh();
}

void MainFrame::ClearPreviousDisplay() {
    if (imageDisplay) {
        imageDisplay->Hide();
    }
    if (animationCtrl) {
        animationCtrl->Stop();
        animationCtrl->Hide();
        GetSizer()->Detach(animationCtrl);
        delete animationCtrl;
        animationCtrl = nullptr;
    }
}

// Manager class implementation
Manager::Manager() {
    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    int windowWidth = screenWidth * 0.75;
    int windowHeight = screenHeight * 0.75;

    mainFrame = new MainFrame("Image Editor", wxDefaultPosition, wxSize(windowWidth, windowHeight));
}

void Manager::ShowMainFrame() {
    mainFrame->Show(true);
}

void Manager::ImportImage() {
    mainFrame->ImportImage();
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
