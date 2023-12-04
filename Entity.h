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
    void DestroyItSelf();
    virtual void OnDestroy();

    Faction GetEntityFaction();
    CollisionType GetEntityCollisionType();
    EntityType GetEntityType();

    virtual sf::CircleShape& GetEntityCircleShape();
    virtual sf::RectangleShape& GetEntityRectangleShape();

    int GetLife();
    void SetLife(int value);
    void DecreaseLife(int value);
    int ClampInteger(int value, int minimum, int maximum);

protected:
    ManagerEntity& managerEntity;
    CollisionDetection& collisionDetection;
    EntityType entityType;
    Faction entityFaction;
    CollisionType collisionType;

    int _life = 100;

};

#endif