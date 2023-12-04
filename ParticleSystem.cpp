#include "ParticleSystem.h"
#include "Entity.h"
#include "EntityEnums.h"
#include "ManagerEntity.h"

ParticleSystem::ParticleSystem(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{

}

void ParticleSystem::Burst(int number, int speed, int lifeTime, int size, sf::Color color)
{
	std::list<Particle*>* newParticles = new std::list<Particle*>;
	for (int i = 0; i < number; i++)
	{
		Particle* particle = new Particle(5, 5, 5, sf::Color::Green);
		newParticles->push_back(particle);
	}
	this->burstLists.push_back(newParticles);
}

void ParticleSystem::MoveParticles(std::list<Particle*>& particlesList)
{
	std::list<Particle*>::iterator it = particlesList.begin();

	while (it != particlesList.end())
	{
		(*it)->Move();
	}
}

void ParticleSystem::Update(sf::RenderWindow& window, float deltaTime)
{
	std::list<std::list<Particle*>*>::iterator it = this->burstLists.begin();

	while (it != this->burstLists.end())
	{
		MoveParticles(*(*it));
	}
}


