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

int Entity::GetLife()
{
    return _life;
}

void Entity::SetLife(int value)
{
    _life = ClampInteger(value, 0, value);

    if (_life <= 0) {
        DestroyItSelf();
    }
}

void Entity::DecreaseLife(int value)
{
    std::cout << "Damaged" << std::endl;
    _life = ClampInteger(_life -= value, 0, 100);

    if (_life <= 0) {

        DestroyItSelf();
    }
}

int Entity::ClampInteger(int value, int minimum, int maximum)
{

    if (value > maximum) {
        value = maximum;
    }

    if (value < minimum) {
        value = minimum;
    }

    return value;
}

template <typename T>
T lerp(const T& a, const T& b, float t) {
    return a + t * (b - a);
}

void Entity::DestroyItSelf()
{
    OnDestroy();
    managerEntity.RemoveEntity(this);
}

void Entity::OnDestroy()
{
}

Entity::~Entity() {}