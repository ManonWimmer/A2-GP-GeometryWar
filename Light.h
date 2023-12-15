#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <list>


#include "RayCast.h"
#include "EntityEnums.h"
#include "Entity.h"


class RayCast;

class Light : public Entity
{

	//Sources utilisés pour faire les lights: 
public:
	Light(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, float radius);
	void UpdateLight(sf::RenderWindow& window, float deltaTime);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;
	void SetPosition(sf::Vector2f position);

private:
	sf::CircleShape _lightShape;
	float _radius;
	float _shadowLength = 1000 ;
	std::list<RayCast> _rays;
};

