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
    void GrayscaleGif();
    void BlurGif();
    void DimImage();
    void LightenImage();
    void PixelateImage();
    void RotateImage();
    MainFrame* mainFrame; // Pointer to the main window

private:

};

// Unique IDs for menu actions
enum {
    ID_IMPORT_IMAGE = wxID_HIGHEST + 1,
    ID_APPLY_GRAYSCALE,
    ID_APPLY_BLUR,
    ID_CLEAR_IMAGES,
    ID_APPLY_GRAYSCALE_GIF = wxID_HIGHEST + 100,
    ID_APPLY_BLUR_GIF,
    ID_APPLY_DIM,
    ID_APPLY_LIGHTEN,
    ID_APPLY_PIXELATE,
    ID_APPLY_ROTATE
};

// MainFrame class declaration
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnMenuImportImage(wxCommandEvent& event); // Event handler for the menu to import an image
    void OnMouseWheel(wxMouseEvent& event); // Event handler for mouse wheel
    void ImportImage(); // Method to handle importing an image without an event
    void OnExportImage(wxCommandEvent& event); // Handels Image Exporting 
    void ImportGifImage(const wxString& path);  // New method for GIFs
    void UpdateImageDisplay(const wxImage& image); // Update the displayed image
    void ClearPreviousDisplay(); // Helper method to clear any existing displays
    

    // Image Visual Effects
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
    void OnMenuApplyPixelate(wxCommandEvent& event);
    void PixelateImage();


    //Tools
    void OnMenuApplyRotate(wxCommandEvent& event);
    void RotateImage();

    // Gif Visual Effects
    void OnMenuApplyGrayscaleGif(wxCommandEvent& event);
    void OnMenuApplyBlurGif(wxCommandEvent& event);
    void GrayscaleGif();
    void BlurGif();
    void OnAnimationTimer(wxTimerEvent& event);

private:
    wxStaticBitmap* imageDisplay; // Pointer to the control where the image will be displayed
    wxAnimationCtrl* animationCtrl; // Control for displaying animated GIFs

    // Stuff for zooming in and out
    wxImage originalImage;
    wxImage currentImage;  // This image will reflect the current state including effects
    double zoomFactor = 1.0;  // Start with no zoom

    // Gif things
    std::vector<wxBitmap> gifFrames; // Vector to hold the processed frames
    wxTimer* animationTimer;         // Timer to change frames
    size_t currentFrameIndex;        // Current frame index

    int rotations = 0;//Rotation count for rotate the image multiple times
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(ID_IMPORT_IMAGE, MainFrame::OnMenuImportImage)
EVT_MENU(wxID_SAVE, MainFrame::OnExportImage)
EVT_MENU(ID_CLEAR_IMAGES, MainFrame::OnMenuClearEffects)
EVT_MENU(ID_APPLY_GRAYSCALE, MainFrame::OnMenuApplyGrayscale)
EVT_MENU(ID_APPLY_BLUR, MainFrame::OnMenuApplyBlur)
EVT_MENU(ID_APPLY_GRAYSCALE_GIF, MainFrame::OnMenuApplyGrayscaleGif)
EVT_MENU(ID_APPLY_BLUR_GIF, MainFrame::OnMenuApplyBlurGif)
EVT_MENU(ID_APPLY_DIM,MainFrame::OnMenuApplyDim)
EVT_MENU(ID_APPLY_LIGHTEN,MainFrame::OnMenuApplyLighten)
EVT_MENU(ID_APPLY_PIXELATE,MainFrame::OnMenuApplyPixelate)
EVT_MENU(ID_APPLY_ROTATE,MainFrame::OnMenuApplyRotate)
EVT_MOUSEWHEEL(MainFrame::OnMouseWheel)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), imageDisplay(nullptr), animationCtrl(nullptr) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_IMPORT_IMAGE, "&Import Image...\tCtrl-I", "Import an image file");
    menuFile->Append(wxID_SAVE, "&Save Image...\tCtrl-S", "Save your Image"); 


    wxMenu* filters = new wxMenu;
    filters->Append(ID_CLEAR_IMAGES, "&Clear All Visual Effects...\tCtrl-C", "Clear all effects from current image");
    filters->Append(ID_APPLY_GRAYSCALE, "&Apply Grayscale to Image...\tCtrl-G", "Convert the current image to grayscale");
    filters->Append(ID_APPLY_BLUR, "&Apply Blur to Image...\tCtrl-B", "Blur the current image");
    filters->Append(ID_APPLY_DIM, "&Apply Dim to image...\tCtrl-D", "Dim the current image");
    filters->Append(ID_APPLY_LIGHTEN, "&Apply Lighten to image...\tCtrl-L", "Lighten the current image");
    filters->Append(ID_APPLY_PIXELATE, "&Pixelate Image...\tCtrl-P", "Pixelate the current image");

    wxMenu* tools = new wxMenu;
    tools->Append(ID_APPLY_ROTATE, "&Rotate the image...\tCtrl-R", "Rotate the current image");

    wxMenu* gifFilters = new wxMenu;
    gifFilters->Append(ID_APPLY_GRAYSCALE_GIF, "&Apply Grayscale to GIF...\tCtrl-Shift-G", "Convert the current GIF to grayscale");
    gifFilters->Append(ID_APPLY_BLUR_GIF, "&Apply Blur to GIF...\tCtrl-Shift-B", "Blur the current GIF");


    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(filters, "&Image Filters");
    menuBar->Append(gifFilters, "&EXPERIMENTAL - Gif Filters");
    menuBar->Append(tools, "&Tools");

    SetMenuBar(menuBar);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    sizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();

    currentFrameIndex = 0;
    animationTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &MainFrame::OnAnimationTimer, this);

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

void MainFrame::OnMenuApplyGrayscaleGif(wxCommandEvent& event) {
    GrayscaleGif();
}

void MainFrame::OnMenuApplyBlurGif(wxCommandEvent& event) {
    BlurGif();
}

void MainFrame::OnMenuApplyDim(wxCommandEvent& event) {
    DimImage();
}

void MainFrame::OnMenuApplyLighten(wxCommandEvent& event) {
    LightenImage();
}

void MainFrame::OnMenuApplyPixelate(wxCommandEvent& event) {
    PixelateImage();
}

void MainFrame::OnMenuClearEffects(wxCommandEvent& event) {
    ClearAllEffects();
}

void MainFrame::ImportGifImage(const wxString& path) {
    wxAnimation animation;
    if (!animation.LoadFile(path)) {
        wxLogError("Failed to load GIF file.");
        return;
    }

    ClearPreviousDisplay(); // Ensure previous displays are cleared

    if (animation.GetFrameCount() > 1) {
        if (!animationCtrl)
            animationCtrl = new wxAnimationCtrl(this, wxID_ANY);
        
        animationCtrl->SetAnimation(animation);
        animationCtrl->Play();
        animationCtrl->Show();
        GetSizer()->Insert(1, animationCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5); // Center the control
        currentImage = animation.GetFrame(0); // Set the first frame as current image
    }
    else {
        wxImage frameImage = animation.GetFrame(0);
        UpdateImageDisplay(frameImage);
    }
    Layout();
    Refresh();

}

void MainFrame::OnMenuApplyRotate(wxCommandEvent& event) {
    RotateImage();
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

void MainFrame::OnExportImage(wxCommandEvent& event) {

    wxFileDialog saveDialog(this, "Save Image File", "", "", "Image files(*.bmp; *.png; *.jpg; *.gif) | *.bmp; *.png; *.jpg *.gif;",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (!originalImage.IsOk()) {
        wxLogError("No Avalible Image to Save");
        return;
    }

    if (saveDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString filePath = saveDialog.GetPath();

    wxBitmap bitmap = imageDisplay->GetBitmap();
    bitmap.ConvertToImage().SaveFile(filePath);

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

void MainFrame::GrayscaleGif() {
    if (!animationCtrl || animationCtrl->GetAnimation().GetFrameCount() == 0) {
        wxLogError("No GIF is currently loaded.");
        return;
    }

    wxAnimation animation = animationCtrl->GetAnimation();
    size_t frameCount = animation.GetFrameCount();
    gifFrames.clear(); // Clear existing frames

    for (size_t i = 0; i < frameCount; ++i) {
        wxImage frameImage = animation.GetFrame(i);
        wxImage grayImage = frameImage.ConvertToGreyscale();
        gifFrames.push_back(wxBitmap(grayImage)); // Store the processed frame
    }

    // Stop and hide the animation control
    animationCtrl->Stop();
    animationCtrl->Hide();

    // Reset the current frame index and restart the timer
    currentFrameIndex = 0;
    animationTimer->Start(100); // Adjust frame delay as needed
}

void MainFrame::BlurGif() {
    if (!animationCtrl || animationCtrl->GetAnimation().GetFrameCount() == 0) {
        wxLogError("No GIF is currently loaded.");
        return;
    }

    wxAnimation animation = animationCtrl->GetAnimation();
    size_t frameCount = animation.GetFrameCount();
    gifFrames.clear(); // Clear existing frames

    for (size_t i = 0; i < frameCount; ++i) {
        wxImage frameImage = animation.GetFrame(i);
        wxImage blurImage = frameImage.Blur(10); // Blur amount can be adjusted
        gifFrames.push_back(wxBitmap(blurImage)); // Store the processed frame
    }

    // Stop and hide the animation control
    animationCtrl->Stop();
    animationCtrl->Hide();

    // Reset the current frame index and restart the timer
    currentFrameIndex = 0;
    animationTimer->Start(100); // Adjust frame delay as needed
}

void MainFrame::OnAnimationTimer(wxTimerEvent& event) {
    if (currentFrameIndex < gifFrames.size()) {
        if (!imageDisplay)
            imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);

        imageDisplay->SetBitmap(gifFrames[currentFrameIndex]);
        imageDisplay->Show();
        currentFrameIndex++;
    }
    else {
        animationTimer->Stop(); // Stop the timer when the last frame is reached
        currentFrameIndex = 0; // Reset the index if you want to loop the animation
    }
    Layout();
    Refresh();
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

void MainFrame::PixelateImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workspace.");
            return;
    }
    //Pixel size
    int pixel = 10;
    //Copy original image
    wxImage pixelImage = originalImage;

    //get colors of pixels
    for (int y = 0; y < pixelImage.GetHeight(); y += pixel) {
        for (int x = 0; x < pixelImage.GetWidth(); x += pixel) {
            int redTotal = 0; 
            int greenTotal = 0; 
            int blueTotal = 0;
            int totalPixel = 0;

            for (int color1 = 0; color1 < pixel && y + color1 < pixelImage.GetHeight(); color1++) {
                for (int color2 = 0; color2 < pixel && x + color2 < pixelImage.GetWidth(); color2++) {
                    redTotal += pixelImage.GetRed(x + color2, y + color1);
                    greenTotal += pixelImage.GetGreen(x + color2, y + color1);
                    blueTotal += pixelImage.GetBlue(x + color2, y + color1);
                    totalPixel++;
                }
            }
            //Average color of pixels
            int redAverage = redTotal / totalPixel;
            int greenAverage = greenTotal / totalPixel;
            int blueAverage = blueTotal / totalPixel;

            //Color pixels with the average color
            for (int color1 = 0; color1 < pixel && y + color1 < pixelImage.GetHeight(); color1++) {
                for (int color2 = 0; color2 < pixel && x + color2 < pixelImage.GetWidth(); color2++) {
                    pixelImage.SetRGB(x + color2, y + color1, redAverage, greenAverage, blueAverage);
                }
            }
        }
    }
    UpdateImageDisplay(pixelImage);
}

void MainFrame::RotateImage() {
    if (!currentImage.IsOk()) {
        wxLogError("No Valid Image In Workspace.");
        return;
    }
    rotations++;
    wxImage rotateImage = currentImage.Rotate90(true);
    UpdateImageDisplay(rotateImage);
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

void Manager::ClearAllEffects() {
    mainFrame->ClearAllEffects();
}
//Apply Dim effect
void Manager::DimImage() {
    mainFrame->DimImage();
}

//Apply Lighten effect
void Manager::LightenImage() {
    mainFrame->LightenImage();
}

//Apply Pixelate effect
void Manager::PixelateImage() {
    mainFrame->PixelateImage();
}

//Apply Rotation
void Manager::RotateImage() {
    mainFrame->RotateImage();
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
