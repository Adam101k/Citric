/*A projecData instance can hold data related to a project in a json file as text
that can latter be used to guide the computer in setting up the project in the workspace

HOW TO USE
	1.	include "projectData.h" at the top of your script
	2. Create and instance of projectData i will call this one myData (but you can use whatever name)
			ProjectData myData = ProjectData("here you can set the name your data will be saved under")
	3. You can save the data with .Save()
			myData.Save();
		This creates a json file on your computer that will remain after the program has stoped
		executing then later you can use .Load("Name of project here") to copy that data into
		any instance of the project data class
			ProjectData myProject = ProjectData("My Project")
			myProject.SetGreyScale(true);
			myProject.Save();

			ProjectData LoadedData = ProjectData();
			LoadedData.Load("My Project");

		Loaded Data Now contains the data from My Project and will be GreyScale
		to check this we could use LoadedData.GetGreyScale which would return True

		Be sure to keep me updated about what else needs to be saved here!

*/
#pragma once
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <wx/wx.h>
#include <cstdio>
using json = nlohmann::json;

//Holds data that can later be saved to a project
class ProjectData
{
public:
	//Constructors
	ProjectData() { name_ = "DefaultProject"; };
	ProjectData(const std::string& name) :name_(name) {}

	std::string GetName() { return myJson_["Name"]; };

	void SetName(const std::string& name) { name_ = name; myJson_["Name"] = name; };

	bool GetGreyScale() { return myJson_["GreyScale"]; };

	void SetGreyScale(bool on) { myJson_["GreyScale"] = on; }

	bool GetBlurred() { return myJson_["Blurred"]; };

	void SetBlurred(bool on) { myJson_["Blurred"] = on; };

	bool GetLighten() { return myJson_["Lighten"]; };

	void SetLighten(bool on) { myJson_["Lighten"] = on; };

	bool GetDim() { return myJson_["Dim"]; }

	void SetDim(bool on) { myJson_["Dim"] = on; };

	bool GetPixelate() { return myJson_["Pixelate"]; };

	void SetPixilate(bool on) { myJson_["Pixelate"] = on; };

	int GetRotate() { return myJson_["Rotate"]; };

	void Rotate() { myJson_["Rotate"] += 1; };

	bool GetRotateY() { return myJson_["RotateY"]; };

	bool GetCropX() { return myJson_["CropX"]; };

	void AddCropX(float crop) { myJson_["CropX"] += crop; };

	bool GetCropY() { return myJson_["CropY"]; };

	void AddCropY(float crop) { myJson_["CropY"] += crop; };

	std::string getBaseImagePath() { return  this->GetName() + "_Base.BMP"; };

	void SetBaseImage(wxBitmap base) { baseImage = base; myJson_["BaseImage"] = this->GetName() + "_Base.BMP"; };

	//Saves the data to a given file location
	bool Save();
	//Searches Saved Data for given project name (string) and puts the information into this project data
	bool Load(const std::string& projectName);

	void Delete(wxString name);

	ProjectData& operator=(const ProjectData& other);


	//Returns a vector with the names of all projects saved so far
	std::vector<wxString> GetAllProjectNames();

private:
	const std::string FILELOCATION = "ProjectsData.json";
	std::string name_;
	wxBitmap baseImage;

	json myJson_{
		{"Name", name_},
		{"GreyScale", false},
		{"Blured", false},
		{"Dim",false},
		{"Lighten" , false},
		{"Pixelate" , false},
		{"Rotate", 0},
		{"CropX", 0.0},
		{"CropY", 0.0},
		{"BaseImage", "BaseImage.BMP"}
	};
};

using json = nlohmann::json;


bool ProjectData::Save()
{

    //Grab All Data
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    if (iFileStream.is_open()) {
        allData = json::parse(iFileStream);
        iFileStream.close();
    }

    //Heres where we will put information once we figure out what needs to be saved 

    allData[name_] = myJson_;


    //Send back new Data 
    std::ofstream oFileStream(FILELOCATION);
    if (oFileStream.is_open()) {
        oFileStream << std::setw(4) << allData << std::endl;
        oFileStream.close();
        if (baseImage.IsOk()) {
            baseImage.ConvertToImage().SaveFile((this->getBaseImagePath()));
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool ProjectData::Load(const std::string& projectName) {

    //Grab All data
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    if (!iFileStream.is_open()) {
        return false;
    }
    allData = json::parse(iFileStream);
    iFileStream.close();


    if (!allData.contains(projectName)) {
        std::cout << "ERROR: Project save data not found for given name";
        return false;
    }
    myJson_ = allData[projectName];
    this->SetName(projectName);
    return true;
}

std::vector<wxString> ProjectData::GetAllProjectNames()
{
    std::vector<wxString> names;
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    allData = json::parse(iFileStream);

    iFileStream.close();

    for (auto it = allData.begin(); it != allData.end(); ++it)
    {
        names.push_back(wxString(it.key()));
    }
    return names;
}


void ProjectData::Delete(wxString name) {

    //Grab All Data
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    if (iFileStream.is_open()) {
        allData = json::parse(iFileStream);
        iFileStream.close();
    }

    std::remove(this->getBaseImagePath().c_str());
    allData.erase(name.ToStdString());


    //Send back new Data 
    std::ofstream oFileStream(FILELOCATION);
    if (oFileStream.is_open()) {
        oFileStream << std::setw(4) << allData << std::endl;
        oFileStream.close();
    }

}

ProjectData& ProjectData::operator=(const ProjectData& other)
{
    if (this != &other) {
        name_ = other.name_;
        baseImage = other.baseImage;

        myJson_ = other.myJson_;
    }
    return *this;
}