#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.cpp"
class AI_Agent : public Entity
{

public:
	void InitializedAgent(int particleID, float radius, sf::Vector2f spawnPosition);
	void Update(sf::RenderWindow& window, float& deltaTime) override;


	bool IsSuperPosed(sf::CircleShape& shape1, sf::CircleShape& shape2);
	void SetTarget(sf::CircleShape& target);
	void Chase(float deltaTime);

	sf::Vector2f NormalizedVector(sf::Vector2f source);
	sf::CircleShape& GetCircle();
	sf::Vector2f& GetDirection();


private:
	int _id;
	sf::CircleShape _circle;
	sf::Vector2f _direction;
	sf::CircleShape& _target;

	float _speed;
	float _mass;

};


