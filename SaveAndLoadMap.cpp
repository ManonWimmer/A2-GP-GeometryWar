#include "SaveAndLoadMap.h"

#include "ManagerEntity.h"
#include "Building.h"
#include "CollisionDetection.h"
#include "GameManager.h"


void SaveAndLoadMap::SaveToJSON(std::list<Building*>& buildingList, std::string fileName) {

    json jsonData;

    //Load Data into Json
    for (Building* building : buildingList) {
        jsonData.push_back(building->SaveBuilding());
    }

    // Save JSON data into a file
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(2);
        outputFile.close();
        std::cout << "JSON data saved to: " << fileName << std::endl;
    }
    else {
        std::cerr << "Error opening file for writing" << std::endl;
    }
}

std::list<Building*>& SaveAndLoadMap::GetBuildings()
{
    return buildings;
}

std::list<Building*> SaveAndLoadMap::LoadFromJSON(std::string fileName, ManagerEntity& managerEntity, CollisionDetection& collisionDetection, bool inEditor) {
    std::list<Building*> loadedBuildingList;

    // Load JSON data from the file
    std::ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        json jsonData;
        inputFile >> jsonData;
        inputFile.close();

        // Get JSON data and create Building objects
        for (auto& buildingData : jsonData) {
            loadedBuildingList.push_back(Building::LoadBuilding(buildingData, managerEntity, collisionDetection, inEditor));
        }

        std::cout << "JSON data loaded from '" << fileName << "'" << std::endl;
    }
    else {
        std::cerr << "Error opening file '" << fileName << "' for reading" << std::endl;
    }

    return loadedBuildingList;
}

void SaveAndLoadMap::LoadMap(std::string fileName, ManagerEntity& managerEntity, CollisionDetection& collisionDetection, bool inEditor)
{
    if(buildings.size() != 0)   ClearCurrentMap(managerEntity);

    buildings = LoadFromJSON(fileName, managerEntity, collisionDetection, inEditor);

    for (Building* building : buildings) {
        managerEntity.AddEntity(building);
    }
}

void SaveAndLoadMap::ClearCurrentMap(ManagerEntity& managerEntity)
{
    std::list<Building*>::iterator it;

    for (it = buildings.begin(); it != buildings.end();) {
        managerEntity.RemoveEntity(*it);
        it = buildings.erase(it);
    }
}
