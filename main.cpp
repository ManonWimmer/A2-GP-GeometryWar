#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "ManagerEntity.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "GameManager.h"
#include "Weapon.h"
#include "EditeurManager.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Menu.h"

int main()
{
	// Initialisation
	//sf::RenderWindow window(sf::VideoMode(720, 480), "James Bond");
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "James Bond");
	window.setVerticalSyncEnabled(true);

	sf::Clock frameClock;

	CollisionDetection collisionDetection;

	ManagerEntity entityManager(&collisionDetection);
	entityManager.InitializedParticles(entityManager);

	GameManager gameManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);
	gameManager.InitializedGameManager(window, gameManager);
	entityManager.AddEntity(&gameManager);

	collisionDetection.SetGameManager(&gameManager);

	//EditeurManager editeurManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);

	bool hasBurst = false;
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialisation random

	while (window.isOpen())
	{
		// G�rer les �v�n�ments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On g�re l'�v�n�ment
			switch (event.type)
			{
				case sf::Event::Closed:
					// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
					window.close();
					break;

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();

		// Remise au noir de toute la fen�tre
		window.clear();

		// Affichage
		entityManager.UpdateAllEntities(window, deltaTime, entityManager);

		//editeurManager.Update(window, deltaTime);

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		//{
		//	if (hasBurst == false)
		//	{
		//		//gameManager.SwitchMode();
		//		hasBurst = true;

		//		camera.ChangeToBig(window);

		//		entityManager.GetParticleSystem().Burst(sf::Vector2f(100, 100), 5, 150, 0.1, 2, sf::Color::Yellow, sf::Vector2f(-1, -1), 360);	// Preset impact de balle
		//	}
		//}
		//else
		//{
		//	hasBurst = false;
		//}

		// On pr�sente la fen�tre sur l'�cran
		window.display();
	}
}