#include "SaveAndLoadMap.h"

void SaveAndLoadMap::SaveToTxt(std::list<Building*>& buildingList, std::string fileName) {
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    for (Building* building : buildingList) {
        building->SaveBuilding(outFile);
    }

    outFile.close();
}

std::list<Building*> SaveAndLoadMap::LoadFromTxt(std::string filePath, ManagerEntity& managerEntity, CollisionDetection& collisionDetection) {
    std::list<Building*> loadedBuildings;


    std::cout << "Launch Load Map: " << filePath << std::endl;

    std::ifstream inFile(filePath);

    std::cout << "after infile initialization" << filePath << std::endl;

    if (!inFile.is_open()) {
        std::cout << "Is file open" << filePath << std::endl;

        std::cerr << "Error opening file for reading: " << filePath << std::endl;
        return loadedBuildings;
    }

    while (!inFile.eof()) {
        Building* loadedBuilding = Building::LoadBuilding(inFile, managerEntity, collisionDetection);

        if (loadedBuilding) {
            loadedBuildings.push_back(loadedBuilding);
        }
    }

    inFile.close();

    return loadedBuildings;
}