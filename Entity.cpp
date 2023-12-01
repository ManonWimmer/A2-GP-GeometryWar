#include "Entity.h"
#include "ManagerEntity.h"
#include "CollisionDetection.h" 

Entity::Entity(ManagerEntity& managerEntity, CollisionDetection& collisionDetection)
    : managerEntity(managerEntity), collisionDetection(collisionDetection) {}



void Entity::UpdateBaseEntity(sf::RenderWindow& window, float deltaTime)
{
    //std::cout << "Entity Collision Updated" << std::endl;
}

Entity::~Entity() {}