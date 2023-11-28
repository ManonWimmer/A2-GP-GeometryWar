#include "ManagerEntity.h"
#include <iostream>
#include <SFML/Graphics.hpp>

//ManagerEntity& Instance() {
//	static ManagerEntity _instance;
//	return _instance;
//}

ManagerEntity& ManagerEntity::Instance()
{
	static ManagerEntity _instance;
	return _instance;
}

void ManagerEntity::Update(sf::RenderWindow& window, float& deltaTime)
{
	std::cout << "Manager Entity Working" << std::endl;
}