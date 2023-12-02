#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "EntityEnums.h"

class GameManager;
class CollisionDetection;
class ManagerEntity;





class Entity {
public:
    Entity(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType);
    virtual ~Entity();

    virtual void Update(sf::RenderWindow& window, float deltaTime) = 0;
    void UpdateBaseEntity(sf::RenderWindow& window, float deltaTime);

    Faction GetEntityFaction();
    CollisionType GetEntityCollisionType();
    EntityType GetEntityType();

    virtual sf::CircleShape& GetEntityCircleShape();
    virtual sf::RectangleShape& GetEntityRectangleShape();

protected:
    ManagerEntity& managerEntity;
    CollisionDetection& collisionDetection;
    EntityType entityType;
    Faction entityFaction;
    CollisionType collisionType;
};

#endif