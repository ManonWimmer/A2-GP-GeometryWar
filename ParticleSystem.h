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

	void MoveParticles(std::list<Particle*>&);

	void Burst(int, int, int, int, sf::Color);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

	std::list<std::list<Particle*>*> burstLists;
	std::list<Particle*> particlesList;
};

