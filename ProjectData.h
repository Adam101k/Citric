
/*A projecData instance can hold data related to a project in a json file as text
that can latter be used to guide the computer in setting up the project in the workspeace 

HOW TO USE
	1.	include "projectData.h" at the top of your script 
	2. Create and instance of projectData i will call this one myData (but you can use whatever name)
			ProjectData myData = ProjectData("here you can set the name your data will be saved under")
	3. You can save the data with .Save() 
			myData.Save();
		This creates a json file on your computer that will remain after the program has stoped 
		exexuteing then later you can use .Load("Name of project here") to copy that data into 
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

	void DeleteProject(std::string name);

	//Saves the data to a given file location
	bool Save();
	//Searches Saved Data for given project name (string) and puts the information into this project data
	bool Load(const std::string& projectName);

	//Returns a vector with the names of all projects saved so far
	std::vector<std::string> GetAllProjectNames();

private:
	//Need to plug in path for where file will go
	const std::string FILELOCATION = "ProjectsData.json";
	std::string name_;

	json myJson_{
		{"Name", name_},
		{"GreyScale", false},
		{"Blured", false}
	};
};




