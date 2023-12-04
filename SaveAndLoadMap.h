#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Building.h"

class SaveAndLoadMap
{
public:
	void SaveToTxt(std::list<Building*>& buildingList, std::string fileName);
	std::list<Building*> LoadFromTxt(std::string filePath, ManagerEntity& managerEntity, CollisionDetection& collisionDetection);
};

