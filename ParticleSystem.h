#pragma once

#include <list>
#include "Particle.h"
#include "Entity.h"
#include "EntityEnums.h"
#include "ManagerEntity.h"

class ParticleSystem : public Entity
{
public:
	
	ParticleSystem(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType);


	void Burst(sf::Vector2f position, int number, float speed, float lifeTime, float size, sf::Color color, sf::Vector2i target, float angle);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

private:
	void MoveParticles(std::list<Particle*>&, float deltaTime, sf::RenderWindow& window);
	std::list<std::list<Particle*>*> burstLists;
	std::list<Particle*> particlesList;
};

