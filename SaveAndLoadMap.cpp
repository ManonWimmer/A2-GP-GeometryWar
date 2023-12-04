#include "SaveAndLoadMap.h"

// Save Buildings* to a text file
void SaveAndLoadMap::SaveToTxt(std::list<Building*>& buildingList, std::string fileName) {
    std::ofstream file(fileName);

    if (file.is_open()) {
        for (Building* building : buildingList) {
            building->SaveBuilding(file);
        }
        file.close();
    }
    else {
        std::cerr << "Error opening file: " << fileName << std::endl;
        std::cerr << "Generating a new file with name: " << fileName << std::endl;

        std::ofstream newFile(fileName, std::ios::app);

        if (!newFile.is_open()) {
            std::cerr << "Error creating file: " << fileName << std::endl;
        }

        std::list<Building*>::iterator it;
        for (it = buildingList.begin(); it != buildingList.end(); it++)
        {
            (*it)->SaveBuilding(newFile);
        }

        newFile.close();
    }
}

// Load Buildings* from a text file
std::list<Building*> SaveAndLoadMap::LoadFromTxt(std::string filePath, ManagerEntity& managerEntity, CollisionDetection& collisionDetection) {
    std::list<Building*> buildingList;

    std::ifstream file(filePath);
    if (file.is_open()) {
        while (!file.eof()) {
            Building* building = Building::LoadBuilding(file, managerEntity, collisionDetection);
            buildingList.push_back(building);
        }
        file.close();
    }
    else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    return buildingList;
}