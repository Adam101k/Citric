
/*A projecData instance can hold dat*/
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

