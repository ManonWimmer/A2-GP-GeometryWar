#pragma once
#include <SFML/Graphics.hpp>
#include "MathLib.h"

#include "EntityEnums.h"

class ManagerEntity;
class Entity;

class RayCast
{
public:
	RayCast(sf::Vector2f origin, sf::Vector2f localDirection, float length, bool drawingOnContact);
	void DrawRayCast(sf::RenderWindow& window, ManagerEntity& managerEntity);
	void CalculNormalizedDirection();
	void CalculateImpactPoint(ManagerEntity& managerEntity);
	void SetRayOrigin(sf::Vector2f vector);


	bool GetContact();
	sf::Vector2f GetImpactPoint();
	sf::Vector2f GetOrigin();
	sf::Vector2f GetLocalDirection();


private:
	sf::Vector2f _origin;
	sf::Vector2f _localDirection;
	sf::Vector2f _normalizedDirection;
	float _length;

	float _distance;
	sf::Vector2f _impactPoint;

	bool _drawingOnContact;
	sf::CircleShape _contactShape;

	bool _contact;
};

