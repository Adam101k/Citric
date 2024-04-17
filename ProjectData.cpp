#include "ProjectData.h"
#include <iostream>
using json = nlohmann::json;

bool ProjectData::Save()
{

    //Grab All Data
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    if (iFileStream.is_open()) {
        iFileStream >> allData;
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
}

bool ProjectData::Load(const std::string& projectName) {

    //Grab All data
    json allData;
    std::ifstream iFileStream(FILELOCATION);
    if (!iFileStream.is_open()) {
        return false;
    }
    allData.parse(iFileStream);
    iFileStream.close();

    //
    myJson_ = allData[projectName];
    this->SetName(projectName);
}
