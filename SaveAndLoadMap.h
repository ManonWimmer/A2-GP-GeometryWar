#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Building.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class SaveAndLoadMap
{
public:
	void SaveToJSON(std::list<Building*>& buildingList, std::string fileName);
	std::list<Building*> LoadFromJSON(std::string filePath, ManagerEntity& managerEntity, CollisionDetection& collisionDetection);
};

