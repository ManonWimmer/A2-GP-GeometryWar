#include "ParticleSystem.h"
#include "Entity.h"
#include "EntityEnums.h"
#include "ManagerEntity.h"

ParticleSystem::ParticleSystem(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{

}

void ParticleSystem::Burst(sf::Vector2f position, int number, float speed, float lifeTime, float size, sf::Color color)
{
	std::list<Particle*>* newParticles = new std::list<Particle*>;
	for (int i = 0; i < number; i++)
	{
		Particle* particle = new Particle(position, speed, lifeTime, size, color);
		newParticles->push_back(particle);
	}
	this->burstLists.push_back(newParticles);
}

void ParticleSystem::MoveParticles(std::list<Particle*>& particlesList, float deltaTime, sf::RenderWindow& window)
{
	std::list<Particle*>::iterator it = particlesList.begin();

	while (it != particlesList.end())
	{
		if ((*it)->currenLifeTime > (*it)->lifeTime)
		{
			it = particlesList.erase(it);
		}
		else 
		{
			//std::cout << "X : " << (*it)->circleShape.getPosition().x << " ; Y : " << (*it)->circleShape.getPosition().y << std::endl;
			(*it)->circleShape.getPosition();
			(*it)->Move(deltaTime);
			window.draw((*it)->circleShape);
			it++;
		}
	}
}

void ParticleSystem::Update(sf::RenderWindow& window, float deltaTime)
{
	std::cout << "Update !!!!!!!" << std::endl;

	std::list<std::list<Particle*>*>::iterator it = this->burstLists.begin();

	while (it != this->burstLists.end())
	{
		if ((*it)->size() <= 0)
		{
			it = this->burstLists.erase(it);
		}
		else 
		{
			MoveParticles(*(*it), deltaTime, window);
			it++;
		}
	}
}


