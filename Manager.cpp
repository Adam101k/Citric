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
    void ClearAllEffects(); // Helper Method to clear effects while keeping the original image on display
    void GrayscaleImage();
    void BlurImage();
    void DimImage();
    void LightenImage();
    MainFrame* mainFrame; // Pointer to the main window

private:

};

// Unique IDs for menu actions
enum {
    ID_IMPORT_IMAGE = wxID_HIGHEST + 1,
    ID_APPLY_GRAYSCALE,
    ID_APPLY_BLUR,
    ID_CLEAR_IMAGES,
    ID_APPLY_DIM,
    ID_APPLY_LIGHTEN
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
    

    // Visual Effects
    void OnMenuClearEffects(wxCommandEvent& event);
    void ClearAllEffects(); // Helper Method to clear effects while keeping the original image on display
    void OnMenuApplyGrayscale(wxCommandEvent& event);
    void GrayscaleImage();
    void OnMenuApplyBlur(wxCommandEvent& event);
    void BlurImage();
    void OnMenuApplyDim(wxCommandEvent& event);
    void DimImage();
    void OnMenuApplyLighten(wxCommandEvent& event);
    void LightenImage();

private:
    wxStaticBitmap* imageDisplay; // Pointer to the control where the image will be displayed
    wxAnimationCtrl* animationCtrl; // Control for displaying animated GIFs

    // Stuff for zooming in and out
    wxImage originalImage;
    wxImage currentImage;  // This image will reflect the current state including effects
    double zoomFactor = 1.0;  // Start with no zoom

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(ID_IMPORT_IMAGE, MainFrame::OnMenuImportImage)
EVT_MENU(ID_CLEAR_IMAGES, MainFrame::OnMenuClearEffects)
EVT_MENU(ID_APPLY_GRAYSCALE, MainFrame::OnMenuApplyGrayscale)
EVT_MENU(ID_APPLY_BLUR, MainFrame::OnMenuApplyBlur)
EVT_MENU(ID_APPLY_DIM,MainFrame::OnMenuApplyDim)
EVT_MENU(ID_APPLY_LIGHTEN,MainFrame::OnMenuApplyLighten)
EVT_MOUSEWHEEL(MainFrame::OnMouseWheel)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), imageDisplay(nullptr), animationCtrl(nullptr) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_IMPORT_IMAGE, "&Import Image...\tCtrl-I", "Import an image file");
    

    wxMenu* filters = new wxMenu;
    filters->Append(ID_CLEAR_IMAGES, "&Clear All Visual Effects...\tCtrl-C", "Clear all effects from current image");
    filters->Append(ID_APPLY_GRAYSCALE, "&Apply Grayscale to Image...\tCtrl-G", "Convert the current image to grayscale");
    filters->Append(ID_APPLY_BLUR, "&Apply Blur to Image...\tCtrl-B", "Blur the current image");
    filters->Append(ID_APPLY_DIM, "&Apply Dim to image...\tCtrl-D", "Dim the current image");
    filters->Append(ID_APPLY_LIGHTEN, "&Apply Lighten to image...\tCtrl-L", "Lighten the current image");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(filters, "&Image Filters");

    SetMenuBar(menuBar);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    sizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();
}

void MainFrame::OnMenuImportImage(wxCommandEvent& event) {
    ImportImage();
}

void MainFrame::OnMenuApplyGrayscale(wxCommandEvent& event) {
    GrayscaleImage();
}

void MainFrame::OnMenuApplyBlur(wxCommandEvent& event) {
    BlurImage();
}

void MainFrame::OnMenuApplyDim(wxCommandEvent& event) {
    DimImage();
}

void MainFrame::OnMenuApplyLighten(wxCommandEvent& event) {
    LightenImage();
}

void MainFrame::OnMenuClearEffects(wxCommandEvent& event) {
    ClearAllEffects();
}

void MainFrame::OnMouseWheel(wxMouseEvent& event) {
    if (!currentImage.IsOk()) {
        // Make sure there's a valid image loaded
        currentImage = imageDisplay->GetBitmap().ConvertToImage();
    }

    int rotation = event.GetWheelRotation();
    if (rotation > 0) {
        zoomFactor *= 1.1;  // Zoom in
    }
    else {
        zoomFactor *= 0.9;  // Zoom out
    }

    if (imageDisplay && currentImage.IsOk()) {
        wxSize originalSize = currentImage.GetSize();
        wxSize newSize(static_cast<int>(originalSize.x * zoomFactor), static_cast<int>(originalSize.y * zoomFactor));
        if (newSize.x > 0 && newSize.y > 0) {
            wxImage scaledImage = currentImage.Scale(newSize.x, newSize.y, wxIMAGE_QUALITY_HIGH);
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
    currentImage = image;  // Update the current image with the new one
    if (!imageDisplay)
        imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    wxImage scaledImage = currentImage.Scale(currentImage.GetWidth(), currentImage.GetHeight(), wxIMAGE_QUALITY_HIGH);
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

void MainFrame::ClearAllEffects() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workplace.");
        return;
    }
    UpdateImageDisplay(originalImage);
}

void MainFrame::GrayscaleImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workplace.");
        return;
    }
    wxImage grayImage = originalImage.ConvertToGreyscale();
    UpdateImageDisplay(grayImage);
}

void MainFrame::BlurImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workplace.");
        return;
    }
    wxImage blurImage = originalImage.Blur(10);
    UpdateImageDisplay(blurImage);
}

void MainFrame::DimImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Vaid Image In Workspace.");
        return;
    }
    wxImage dimImage = originalImage.ConvertToDisabled(10);
    UpdateImageDisplay(dimImage);
}

void MainFrame::LightenImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workspace.");
        return;
    }
    wxImage lightenImage = originalImage.ChangeLightness(110);
    UpdateImageDisplay(lightenImage);
}

// Manager Class Decleration
Manager::Manager() {
    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    int windowWidth = screenWidth * 0.75;
    int windowHeight = screenHeight * 0.75;

    mainFrame = new MainFrame("Image Editor", wxDefaultPosition, wxSize(windowWidth, windowHeight));
}

// Show the main window
void Manager::ShowMainFrame() {
    mainFrame->Show(true);
}

// Import image to the workspace
void Manager::ImportImage() {
    mainFrame->ImportImage();
}

// Apply grayscale effect
void Manager::GrayscaleImage() {
    mainFrame->GrayscaleImage();  // No parameter is needed; it directly uses the original image within MainFrame
}

// Apply blur effect
void Manager::BlurImage() {
    mainFrame->BlurImage();
}

//Apply Dim effect
void Manager::DimImage() {
    mainFrame->DimImage();
}

//Apply Lighten effect
void Manager::LightenImage() {
    mainFrame->LightenImage();
}

// wxWidgets application entry point
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
