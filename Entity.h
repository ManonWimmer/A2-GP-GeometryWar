#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class CollisionDetection;
class ManagerEntity;

class Entity {
public:
    Entity(ManagerEntity& managerEntity, CollisionDetection& collisionDetection);
    virtual ~Entity();

    virtual void Update(sf::RenderWindow& window, float deltaTime) = 0;
    void UpdateBaseEntity(sf::RenderWindow& window, float deltaTime);

protected:
    ManagerEntity& managerEntity;
    CollisionDetection& collisionDetection;
};

#endif