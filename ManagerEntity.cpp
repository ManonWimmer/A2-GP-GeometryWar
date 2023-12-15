#include "ManagerEntity.h"
#include "EntityEnums.h"
#include "Entity.h"
#include "AI_Agent.h"
#include "CollisionDetection.h" 
#include "ParticleSystem.h"


ManagerEntity::ManagerEntity(CollisionDetection* collisionDetection, sf::RenderWindow* window) 
    : collisionDetection(collisionDetection), _window(window) {}

void ManagerEntity::AddEntity(Entity* entity) {
    entityDictionary[entity] = true;
}

std::unordered_map<Entity*, bool>::iterator ManagerEntity::GetPair(Entity* entity)
{
    auto it = entityDictionary.find(entity);

    if (it != entityDictionary.end()) {
        return it;  // Dereference the iterator to get the value (std::pair<Entity*, bool>)
    }
    else {
        //Error
        return it;
    }
}

void ManagerEntity::RemoveEntity(Entity* entity) {
    //iterator = entityDictionary.erase(iterator);
    entityGarbage.insert(entity);
}

bool ManagerEntity::IsEntityActive(Entity* entity) {
    auto it = entityDictionary.find(entity);
    return it != entityDictionary.end() && it->second;
}

void ManagerEntity::UpdateAllEntities(sf::RenderWindow& window, float deltaTime, ManagerEntity& managerEntity) {

    // Updating Player & All AI & Weapons & Bullets for first drawed layer (under shadow layer)
    for (auto& pair : entityDictionary) {
        if (pair.first->GetEntityType() != EntityType::AI_Entity && 
            pair.first->GetEntityType() != EntityType::Player_Entity && 
            pair.first->GetEntityType() != EntityType::Weapon_Entity && 
            pair.first->GetEntityType() != EntityType::Projectile_Entity
            ) continue;

        if (pair.second) {
            pair.first->Update(window, deltaTime);
            pair.first->UpdateBaseEntity(window, deltaTime);
        }
    }


    // Updating Light & Shadows for second drawed layer
    for (auto& pair : entityDictionary) {
        if (pair.first->GetEntityType() != EntityType::Light_Entity) continue;

        if (pair.second) {
            pair.first->Update(window, deltaTime);
            pair.first->UpdateBaseEntity(window, deltaTime);
        }
    }

    // Updating others for third layer (Buildings)
    for (auto& pair : entityDictionary) {
        if (pair.first->GetEntityType() == EntityType::Light_Entity || 
            pair.first->GetEntityType() == EntityType::AI_Entity || 
            pair.first->GetEntityType() == EntityType::Player_Entity || 
            pair.first->GetEntityType() == EntityType::Weapon_Entity || 
            pair.first->GetEntityType() == EntityType::Projectile_Entity
            ) continue;

        if (pair.second) {
            pair.first->Update(window, deltaTime);
            pair.first->UpdateBaseEntity(window, deltaTime);
        }
    }


    collisionDetection->CheckAllEntitiesCollisions(managerEntity);
    
    ClearEntityGarbage();
}

void ManagerEntity::ClearEntityGarbage()
{

    std::set<Entity*>::iterator it = entityGarbage.begin();

    while (it != entityGarbage.end()) {

        if (*it != nullptr) {
            entityDictionary.erase(*it);

            delete *it;
        }

        it = entityGarbage.erase(it);
    }

}

void ManagerEntity::DebugEntities(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, Player& player)
{
    AddEntity(new AI_Agent(managerEntity, collisionDetection, EntityType::AI_Entity, Faction::EnemiesFaction, CollisionType::Circle, 17.0f, sf::Vector2f(600, 600), 75.0f, player));
}

void ManagerEntity::InitializedParticles(ManagerEntity& managerEntity)
{
    _particleSystem = new ParticleSystem(managerEntity, *collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);
    AddEntity(_particleSystem);
}

std::unordered_map<Entity*, bool>& ManagerEntity::GetEntityDictionary()
{
    return entityDictionary;
}

std::set<Entity*>& ManagerEntity::GetEntityGarbage()
{
    return entityGarbage;
}

ParticleSystem& ManagerEntity::GetParticleSystem()
{
    return *_particleSystem;
}

sf::RenderWindow& ManagerEntity::GetRenderWindow()
{
    return *_window;
}

