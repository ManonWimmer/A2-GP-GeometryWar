#include "ParticleSystem.h"
#include "Entity.h"
#include "EntityEnums.h"
#include "ManagerEntity.h"

ParticleSystem::ParticleSystem(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{

}

void ParticleSystem::Burst(sf::Vector2f position, int number, float speed, float lifeTime, float size, sf::Color color, sf::Vector2f target, float angle)
{
	std::list<Particle*>* newParticles = new std::list<Particle*>;
	for (int i = 0; i < number; i++)
	{
		Particle* particle = new Particle(position, speed, lifeTime, size, color, target, angle);
		newParticles->push_back(particle);
	}
	burstLists.push_back(newParticles);
}

void ParticleSystem::MoveParticles(std::list<Particle*>& particlesList, float deltaTime, sf::RenderWindow& window)
{
	std::list<Particle*>::iterator it = particlesList.begin();

	while (it != particlesList.end())
	{
		if ((*it)->currenLifeTime > (*it)->lifeTime)
		{
			delete* it;
			it = particlesList.erase(it);
		}
		else 
		{
			(*it)->circleShape.getPosition();
			(*it)->Move(deltaTime);
			(*it)->currenLifeTime += deltaTime;
			window.draw((*it)->circleShape);
			it++;
		}
	}
}

void ParticleSystem::Update(sf::RenderWindow& window, float deltaTime)
{
	std::list<std::list<Particle*>*>::iterator it = this->burstLists.begin();

	while (it != this->burstLists.end())
	{
		if ((*it)->size() <= 0)
		{
			delete* it;
			it = burstLists.erase(it);
		}
		else 
		{
			MoveParticles(*(*it), deltaTime, window);
			it++;
		}
	}
}


