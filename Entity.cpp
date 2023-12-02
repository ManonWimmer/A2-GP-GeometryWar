#include "Entity.h"
#include "ManagerEntity.h"
#include "CollisionDetection.h" 
#include "GameManager.h"

Entity::Entity(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType) 
    : managerEntity(managerEntity), collisionDetection(collisionDetection), entityType(entityType), entityFaction(entityFaction), collisionType(collisionType) {}



void Entity::UpdateBaseEntity(sf::RenderWindow& window, float deltaTime)
{
    //std::cout << "Entity Collision Updated" << std::endl;
}

Faction Entity::GetEntityFaction()
{
    return entityFaction;
}

CollisionType Entity::GetEntityCollisionType()
{
    return collisionType;
}

EntityType Entity::GetEntityType()
{
    return entityType;
}

sf::CircleShape& Entity::GetEntityCircleShape()
{
    return (*new sf::CircleShape);
}

sf::RectangleShape& Entity::GetEntityRectangleShape()
{
    return (*new sf::RectangleShape);
}

Entity::~Entity() {}