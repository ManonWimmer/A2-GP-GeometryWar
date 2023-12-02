#include "projectile.h"
#include <SFML/Graphics.hpp>

Projectile::Projectile(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f origin, sf::Vector2f direction, float currentTime, int speed, sf::CircleShape projectileShape)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{
	this->_origin = origin;
	this->_direction = direction;
	this->CurrentTime = currentTime;
	this->_speed = speed;
	this->ProjectileShape = projectileShape;
}

void Projectile::Update(sf::RenderWindow& window, float deltaTime)
{
	MoveProjectile(deltaTime);
	window.draw(ProjectileShape);
}

sf::CircleShape& Projectile::GetEntityCircleShape()
{
	return ProjectileShape;
}

void Projectile::MoveProjectile(float deltaTime)
{
	sf::Vector2f movement = _direction * static_cast<float>(_speed) * deltaTime;



	ProjectileShape.move(movement);
}