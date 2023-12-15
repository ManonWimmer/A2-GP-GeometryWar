#include "RayCast.h"

#include "ManagerEntity.h"
#include "Entity.h"
#include <iostream>


RayCast::RayCast(sf::Vector2f origin, sf::Vector2f localDirection, float length, bool drawingOnContact)
{
	_origin = origin;
	_localDirection = localDirection;
	_length = length;
	_distance = _length;
	_drawingOnContact = drawingOnContact;
	_impactPoint = sf::Vector2f(0, 0);

	CalculNormalizedDirection();

	_contactShape.setFillColor(sf::Color::Red);
	_contactShape.setRadius(5.0f);
	_contactShape.setOrigin(_contactShape.getRadius(), _contactShape.getRadius());
}

void RayCast::DrawRayCast(sf::RenderWindow& window, ManagerEntity& managerEntity)
{
	CalculateImpactPoint(managerEntity);

	if (_drawingOnContact) {

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(_origin.x, _origin.y), sf::Color::White),
			sf::Vertex(sf::Vector2f(_impactPoint.x, _impactPoint.y), sf::Color::Red)
		};

		window.draw(line, 2, sf::Lines);
		
		_contactShape.setPosition(_impactPoint);
		window.draw(_contactShape);
	}

	//std::cout << "Impact Point: " << _impactPoint.x << " ; " << _impactPoint.y << std::endl;

}

void RayCast::CalculNormalizedDirection()
{
	_normalizedDirection = MathLib::NormalizedVector(_localDirection);
}

void RayCast::CalculateImpactPoint(ManagerEntity& managerEntity)
{
	sf::Vector2f* intersectionPoint = new sf::Vector2f();
	_contact = false;


	for (auto x = managerEntity.GetEntityDictionary().begin(); x != managerEntity.GetEntityDictionary().end(); ++x)
	{
		float newDistance = FLT_MAX;

		// Check if the entity have collision
		if (x->first->GetEntityCollisionType() == CollisionType::None_CollisionType) continue;

		//check if it's the player
		if (x->first->GetEntityType() == EntityType::Player_Entity) continue;

		//std::cout << "RAy cast working" << std::endl;

		
		switch (x->first->GetEntityCollisionType()) {
			case CollisionType::Circle:
				if (MathLib::IsRayCircleIntersection(_origin, _localDirection, x->first->GetEntityCircleShape(), *intersectionPoint)) {

					//std::cout << "Ray contact with circle" << std::endl;
					newDistance = MathLib::GetDistanceBetweenVectors(_origin, *intersectionPoint);

					if (newDistance < _length) {
						_contact = true;
					}
					std::cout << "Distance Circle: " << newDistance << std::endl;

				}
				break;

			case CollisionType::Rectangle:

				if (MathLib::IsRayRectangleIntersection(_origin, _localDirection, x->first->GetEntityRectangleShape(), *intersectionPoint)) {

					newDistance = MathLib::GetDistanceBetweenVectors(_origin, *intersectionPoint);
					if (newDistance < _length) {
						_contact = true;
					}
					//std::cout << "Distance Rectangle: " << newDistance << std::endl;
					//std::cout << "Impact Point: " << intersectionPoint->x << " ; " << intersectionPoint->y << std::endl;

				}
				break;
		}


		if (_contact && newDistance < _distance) {
			_distance = newDistance;
			_impactPoint = *intersectionPoint;
			//std::cout << "Impact Point: " << _impactPoint.x << " ; " << _impactPoint.y << std::endl;
		}


		if (!_contact) {
			_distance = _length;
			_impactPoint = _origin + (_normalizedDirection * _length);
		}

		

	}

	delete intersectionPoint;
}

void RayCast::SetRayOrigin(sf::Vector2f vector)
{
	_origin = vector;
}

bool RayCast::GetContact()
{
	return _contact;
}

sf::Vector2f RayCast::GetImpactPoint()
{
	//std::cout << "Impact Point: " << _impactPoint.x << " ; " << _impactPoint.y << std::endl;

	return _impactPoint;
}

sf::Vector2f RayCast::GetOrigin()
{
	return _origin;
}

sf::Vector2f RayCast::GetLocalDirection()
{
	return _localDirection;
}
