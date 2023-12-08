#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ManagerEntity;
class Building;
class CollisionDetection;

class SaveAndLoadMap
{
public:
	void LoadMap(std::string fileName, ManagerEntity& managerEntity, CollisionDetection& collisionDetection);
	void ClearCurrentMap(ManagerEntity& managerEntity);

	void SaveToJSON(std::list<Building*>& buildingList, std::string fileName);
	std::list<Building*> LoadFromJSON(std::string filePath, ManagerEntity& managerEntity, CollisionDetection& collisionDetection);

	std::list<Building*>& GetBuildings();

private:
	std::list<Building*> buildings;

};

