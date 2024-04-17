
/*HOW TO USE THIS:
  The project data class is desinged to serve as a container for information about projects as they are being
  worked on currently it contains a number as an example but as we build the project we can add all types of information
  be they strings vectors or whatever we want to keep track of what is going on with a perticular project

  How to make a projectData object 

  1. at the top of you script type: #inlcude "ProjectData.h"

  2. Declare it as you would do with a data type using ProjectData's contructor function 
	(im calling this one myData but you can you use any name you like):
		ProjectData myData = ProjectData("Name of the project goes here");

	Once a project data has been declared you can use its Get and Set functions to refrence and change
	the variables inside 

		myData.GetNumber(); //will return the value of the number
		myData.SetNumber(5); //will set the value of the number to 5

	As you work be sure to let me know of any getters or setters you would like me to add and I will be
	sure to impliment with as promptly as I am able.

	HOW TO SAVE AND LOAD STUFF:
	calling myData.Save(); will either create or modify a json file within the repository that will store 
	all the projects information under its name at the time of saving once that has been done you can load 
	that information onto ANY projectData object even after you stop running the program or in a different script
	
	EXAMPLE:
	
	#include "ProjectData.h"

	ProjectData saveingData =  ProjectData("My Data");
	saveingData.SetNumber(3);

	//Now imagine we run the program once and then delete the above or go into a new script and write 

	#include "ProjectData.h"

	ProjectData loadingData =  ProjectData("Some New Data");
	ProjectData.Load("MyData");

	std::cout << loadingData.GetNumber(5) << " " << loadingData.GetName();

	Console output:
	5 MyData

	Notice the number is still 5 even though we did not set it this time when we ran the program

*/
#pragma once
#include <iostream>
#include "json.hpp"
#include <fstream>
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
	
	
	
	int  GetNumber() {
		return myJson_["Number"];
	};
	void SetNumber(int num) {
		myJson_["Number"] = num;
	}

	//Saves the data to a given file location
	bool Save();
	bool Load(const std::string& projectName);

private:
	//Need to plug in path for where file will go
	const std::string FILELOCATION = "ProjectsData.json";
	std::string name_;

	json myJson_{
		{"Name", name_},
		{"Number", 4}
	};
};

