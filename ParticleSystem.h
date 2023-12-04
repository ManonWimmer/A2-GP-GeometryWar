#pragma once

#include <list>
#include "Particle.h"

class ParticleSystem
{
	ParticleSystem();

public:
	void Burst(int, int, int, int, sf::Color);


	std::list<std::list<Particle>> burstLists;
	std::list<int> particlesList;
};

