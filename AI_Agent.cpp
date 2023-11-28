#include "AI_Agent.h"
#include <iostream>
void AI_Agent::InitializedAgent(int particleID, float radius, sf::Vector2f spawnPosition)
{
	_id = particleID;
	_circle.setFillColor(sf::Color::Yellow);
	_circle.setRadius(radius);
	_circle.setOrigin(_circle.getRadius(), _circle.getRadius());
	_circle.setPosition(spawnPosition);
}

void AI_Agent::Update(sf::RenderWindow& window, float& deltaTime)
{
	std::cout << "AI Agent Entity Working" << std::endl;
	window.draw(_circle);
}

void AI_Agent::SetTarget(sf::CircleShape& target) {
	_target = target;
}
void AI_Agent::Chase(float deltaTime)
{
	sf::Vector2f vecteurDirecteur = _target.getPosition() - _circle.getPosition();
	_circle.move(vecteurDirecteur * _speed * deltaTime);
}