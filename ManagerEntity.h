#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Entity.h"
class ManagerEntity: public Entity
{
public:
	std::list<Entity*> entityList;
	static ManagerEntity& Instance();
	void Update(sf::RenderWindow& window, float& deltaTime) override;

};