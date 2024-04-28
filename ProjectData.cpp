#include "ProjectData.h"
#include <iostream>
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
        return true;
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

std::vector<std::string> ProjectData::GetAllProjectNames()
{
    std::vector<std::string> names;
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    allData = json::parse(iFileStream);

    iFileStream.close();

    for (auto it = allData.begin(); it != allData.end(); ++it)
    {
        names.push_back(it.key());
    }
    return names;
}

void DeleteProject(std::string name) {


}

