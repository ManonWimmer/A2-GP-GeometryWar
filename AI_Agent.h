#ifndef AI_AGENT_H
#define AI_AGENT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

class AI_Agent : public Entity {
public:
    AI_Agent(ManagerEntity& managerEntity, float radius, sf::Vector2f spawnPosition, float speed);

    void SetTarget(sf::CircleShape* target);
    void Chase(float deltaTime);

    sf::Vector2f NormalizedVector(sf::Vector2f source);
    sf::CircleShape& GetCircle();
    sf::Vector2f& GetDirection();

    // function update
    virtual void Update(sf::RenderWindow& window, float deltaTime) override;

private:
    sf::CircleShape _circle;
    sf::Vector2f _direction;
    sf::CircleShape* _target = nullptr;
    float _speed;
};

#endif


