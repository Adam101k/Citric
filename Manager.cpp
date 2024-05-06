#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/statbmp.h>
#include <wx/animate.h>
#include <stack>
#include <wx/button.h>
#include "ProjectData.h"
#include <wx/choice.h>

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
    void UndoAction();
    void RedoAction();

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
    ID_APPLY_ROTATE,
    ID_UNDO,
    ID_REDO,
    ID_SAVE,
    ID_LOAD_DATA,
    ID_EXPORT,
    ID_DELETE,
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
    void OnSaveProject(wxCommandEvent& event);
    void SaveProject();
    void OnLoadProject(wxCommandEvent& event);
    void LoadProject();
    void OnDeleteProject(wxCommandEvent& event);


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
    void OnMenuApplyUndo(wxCommandEvent& event);
    void UndoAction();
    void OnMenuApplyRedo(wxCommandEvent& event);
    void RedoAction();

    // Gif Visual Effects
    void OnMenuApplyGrayscaleGif(wxCommandEvent& event);
    void OnMenuApplyBlurGif(wxCommandEvent& event);
    void GrayscaleGif();
    void BlurGif();
    void OnAnimationTimer(wxTimerEvent& event);

    // Advanced GUI button stuff
    void BindButtonEvents();
    void AddButtonsToSizer(wxGridSizer* gridSizer);

private:
    wxPanel* buttonPanel;
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
    std::stack<wxImage> previousImage; //Stack that stores previous states of the image
    std::stack<wxImage> nextImage; //Stack that stores next state of the image

    ProjectData currentData = ProjectData();

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(ID_IMPORT_IMAGE, MainFrame::OnMenuImportImage)
EVT_MENU(ID_EXPORT, MainFrame::OnExportImage)
EVT_MENU(ID_CLEAR_IMAGES, MainFrame::OnMenuClearEffects)
EVT_MENU(ID_APPLY_GRAYSCALE, MainFrame::OnMenuApplyGrayscale)
EVT_MENU(ID_APPLY_BLUR, MainFrame::OnMenuApplyBlur)
EVT_MENU(ID_APPLY_GRAYSCALE_GIF, MainFrame::OnMenuApplyGrayscaleGif)
EVT_MENU(ID_APPLY_BLUR_GIF, MainFrame::OnMenuApplyBlurGif)
EVT_MENU(ID_APPLY_DIM, MainFrame::OnMenuApplyDim)
EVT_MENU(ID_APPLY_LIGHTEN, MainFrame::OnMenuApplyLighten)
EVT_MENU(ID_APPLY_PIXELATE, MainFrame::OnMenuApplyPixelate)
EVT_MENU(ID_APPLY_ROTATE, MainFrame::OnMenuApplyRotate)
EVT_MENU(ID_UNDO, MainFrame::OnMenuApplyUndo)
EVT_MENU(ID_REDO, MainFrame::OnMenuApplyRedo)
EVT_MENU(ID_SAVE, MainFrame::OnSaveProject)
EVT_MENU(ID_LOAD_DATA, MainFrame::OnLoadProject)
EVT_MENU(ID_DELETE, MainFrame::OnDeleteProject)
EVT_MOUSEWHEEL(MainFrame::OnMouseWheel)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxPanel* imagePanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* imageSizer = new wxBoxSizer(wxVERTICAL);
    imageDisplay = new wxStaticBitmap(imagePanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    imageSizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 5);
    imagePanel->SetSizer(imageSizer);

    buttonPanel = new wxPanel(this, wxID_ANY);
    wxGridSizer* gridSizer = new wxGridSizer(3, 4, 10, 10); // 3 rows, 4 columns

    // Add buttons to the grid sizer
    AddButtonsToSizer(gridSizer);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(gridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
    buttonPanel->SetSizer(buttonSizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(imagePanel, 1, wxEXPAND);
    mainSizer->Add(buttonPanel, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM);

    SetSizer(mainSizer);

    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    // Set full-screen and ensure the window does not go below a specific size
    SetMinSize(wxSize(screenWidth * 0.75, screenHeight * 0.75));
    Maximize();

    BindButtonEvents();

    Layout();
    Centre();
}

void MainFrame::AddButtonsToSizer(wxGridSizer* gridSizer) {
    // Helper function to add buttons to the sizer
    gridSizer->Add(new wxButton(buttonPanel, ID_IMPORT_IMAGE, "Import Image"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_GRAYSCALE, "Grayscale"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_BLUR, "Blur"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_CLEAR_IMAGES, "Clear Effects"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_GRAYSCALE_GIF, "Grayscale GIF"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_BLUR_GIF, "Blur GIF"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_DIM, "Dim"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_LIGHTEN, "Lighten"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_PIXELATE, "Pixelate"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_APPLY_ROTATE, "Rotate"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_UNDO, "Undo"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_REDO, "Redo"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_SAVE, "Save"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_EXPORT, "Export"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_LOAD_DATA, "Load"), 1, wxEXPAND);
    gridSizer->Add(new wxButton(buttonPanel, ID_DELETE, "DeleteProject"), 1, wxEXPAND);
}

void MainFrame::BindButtonEvents() {
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuImportImage, this, ID_IMPORT_IMAGE);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyGrayscale, this, ID_APPLY_GRAYSCALE);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyBlur, this, ID_APPLY_BLUR);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuClearEffects, this, ID_CLEAR_IMAGES);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyGrayscaleGif, this, ID_APPLY_GRAYSCALE_GIF);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyBlurGif, this, ID_APPLY_BLUR_GIF);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyDim, this, ID_APPLY_DIM);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyLighten, this, ID_APPLY_LIGHTEN);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyPixelate, this, ID_APPLY_PIXELATE);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyRotate, this, ID_APPLY_ROTATE);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyUndo, this, ID_UNDO);
    Bind(wxEVT_BUTTON, &MainFrame::OnMenuApplyRedo, this, ID_REDO);
    Bind(wxEVT_BUTTON, &MainFrame::OnExportImage, this, ID_EXPORT);
    Bind(wxEVT_BUTTON, &MainFrame::OnSaveProject, this, ID_SAVE);
    Bind(wxEVT_BUTTON, &MainFrame::OnLoadProject, this, ID_LOAD_DATA);
    Bind(wxEVT_BUTTON, &MainFrame::OnDeleteProject, this, ID_DELETE);
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

void MainFrame::OnMenuApplyUndo(wxCommandEvent& event) {
    UndoAction();
}

void MainFrame::OnMenuApplyRedo(wxCommandEvent& event) {
    RedoAction();
}

void MainFrame::OnSaveProject(wxCommandEvent& event) {
    SaveProject();
}

void MainFrame::OnLoadProject(wxCommandEvent& event) {
    LoadProject();
}

void MainFrame::OnMouseWheel(wxMouseEvent& event) {
    if (!currentImage.IsOk()) return;

    double factor = (event.GetWheelRotation() > 0) ? 1.1 : 0.9;
    zoomFactor *= factor;
    wxSize newSize = wxSize(currentImage.GetWidth() * zoomFactor, currentImage.GetHeight() * zoomFactor);

    if (newSize.x > 1 && newSize.y > 1) {
        wxImage scaledImage = currentImage.Scale(newSize.x, newSize.y, wxIMAGE_QUALITY_HIGH);
        imageDisplay->SetBitmap(wxBitmap(scaledImage));
        imageDisplay->Layout(); // Re-layout the image panel
        imageDisplay->Centre();
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

    if (!originalImage.IsOk() && !animationCtrl) {
        wxLogError("No Available Image or Gif to Save");
        return;
    }

    if (saveDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    // If there's an image, export the image, if not, then it's a gif cause the error catcher would've noticed otherwise
    if (originalImage.IsOk()) {
        wxString filePath = saveDialog.GetPath();

        wxBitmap bitmap = imageDisplay->GetBitmap();
        bitmap.ConvertToImage().SaveFile(filePath);
    }
    else {
        wxLogError("Gif Exporting not supported currently!");
    }
}

void MainFrame::SaveProject() {
    wxString name = wxGetTextFromUser(wxString("Save Project"), wxString("Save as:"), wxString(currentData.GetName()));
    currentData.SetName(name.ToStdString());
    currentData.SetBaseImage(originalImage);
    currentData.Save();
}

void MainFrame::LoadProject() {

    std::vector<wxString> projectNames = currentData.GetAllProjectNames();
    wxString selectedProject;

    wxString name = wxGetTextFromUser(wxString("Load Project"), wxString("Enter Name to Load"), wxString(currentData.GetName()));

    currentData.Load(name.ToStdString());

    wxString path = wxString(currentData.getBaseImagePath());
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
    if (currentData.GetGreyScale()) {
        GrayscaleImage();
    }
    if (currentData.GetBlurred()) {
        BlurImage();
    }
    if (currentData.GetDim()) {
        DimImage();
    }
    if (currentData.GetLighten()) {
        LightenImage();
    }
    if (currentData.GetPixelate()) {
        PixelateImage();
    }
    for (int i = 1; i < currentData.GetRotate(); i++);
    {
        RotateImage();
    }
}

void MainFrame::OnDeleteProject(wxCommandEvent& event) {
    wxString name = wxGetTextFromUser(wxString("DeleteProject"), wxString("Enter Name to Delete"), wxString(currentData.GetName()));
    currentData.Delete(name);
}

void MainFrame::UpdateImageDisplay(const wxImage& image) {
    currentImage = image;  // Update the current image with the new one
    if (!imageDisplay)
        imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    wxImage scaledImage = currentImage.Scale(currentImage.GetWidth(), currentImage.GetHeight(), wxIMAGE_QUALITY_HIGH);
    imageDisplay->SetBitmap(wxBitmap(scaledImage));
    imageDisplay->Show();
    if (animationCtrl) animationCtrl->Hide();

    imageDisplay->Centre();
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

    ProjectData resetData = ProjectData(currentData.GetName());
    currentData = resetData;
}

void MainFrame::GrayscaleImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workplace.");
        return;
    }
    previousImage.push(currentImage);
    wxImage grayImage = originalImage.ConvertToGreyscale();
    UpdateImageDisplay(grayImage);
    currentData.SetGreyScale(true);
}

void MainFrame::BlurImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workplace.");
        return;
    }
    previousImage.push(currentImage);
    wxImage blurImage = originalImage.Blur(10);
    UpdateImageDisplay(blurImage);
    currentData.SetBlurred(true);
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

    currentData.SetGreyScale(true);
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

    currentData.SetBlurred(true);
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
    previousImage.push(currentImage);
    wxImage dimImage = originalImage.ConvertToDisabled(10);
    UpdateImageDisplay(dimImage);
    currentData.SetDim(true);
}

void MainFrame::LightenImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workspace.");
        return;
    }
    previousImage.push(currentImage);
    wxImage lightenImage = originalImage.ChangeLightness(110);
    UpdateImageDisplay(lightenImage);
    currentData.SetLighten(true);
}

void MainFrame::PixelateImage() {
    if (!originalImage.IsOk()) {
        wxLogError("No Valid Image In Workspace.");
        return;
    }
    previousImage.push(currentImage);
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

    currentData.SetPixilate(true);
}

void MainFrame::RotateImage() {
    if (!currentImage.IsOk()) {
        wxLogError("No Valid Image In Workspace.");
        return;
    }
    previousImage.push(currentImage);
    rotations++;
    wxImage rotateImage = currentImage.Rotate90(true);
    UpdateImageDisplay(rotateImage);
    currentData.Rotate();
}

void MainFrame::UndoAction() {
    if (previousImage.empty()) {
        wxLogError("No Actions to Undo.");
        return;
    }
    nextImage.push(currentImage);
    wxImage previousState = previousImage.top();
    previousImage.pop();
    currentImage = previousState;
    UpdateImageDisplay(currentImage);
}

void MainFrame::RedoAction() {
    if (nextImage.empty()) {
        wxLogError("No Actions to Redo.");
        return;
    }
    previousImage.push(currentImage);
    wxImage nextState = nextImage.top();
    nextImage.pop();
    currentImage = nextState;
    UpdateImageDisplay(currentImage);
}
// Manager Class Decleration
Manager::Manager() {
    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    int windowWidth = screenWidth * 0.75;
    int windowHeight = screenHeight * 0.75;

    mainFrame = new MainFrame("Citric", wxDefaultPosition, wxSize(windowWidth, windowHeight));
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

void Manager::UndoAction() {
    mainFrame->UndoAction();
}

void Manager::RedoAction() {
    mainFrame->RedoAction();
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