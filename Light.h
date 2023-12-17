#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <list>


#include "EntityEnums.h"
#include "Entity.h"


class RayCast;

class Light : public Entity
{
public:
	Light(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, float radius);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;
	void SetPosition(sf::Vector2f position);
	void InitializedRays();

private:
	sf::CircleShape _lightShape;
	sf::Color _shadowColor = sf::Color::Black;
	float _radius;
	float _shadowLength = 1000 ;
	std::list<RayCast> _rays;
};

