#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class ManagerEntity;

class Entity {
public:
    Entity(ManagerEntity& managerEntity);
    virtual ~Entity();

    virtual void Update(sf::RenderWindow& window, float deltaTime) = 0;

protected:
    ManagerEntity& managerEntity;
};

#endif