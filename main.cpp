#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "ManagerEntity.h"
#include "CollisionDetection.h"
#include "Player.h"
constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);



	sf::Clock frameClock;
	ManagerEntity entityManager;
	CollisionDetection collisionDetection;
	Player player(entityManager, collisionDetection);
	entityManager.AddEntity(&player);

	entityManager.DebugEntities(entityManager, collisionDetection, player);




	while (window.isOpen())
	{
		
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
				case sf::Event::Closed:
					// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
					window.close();
					break;

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();


		
		// Remise au noir de toute la fenêtre
		window.clear();


		// Affichage
		entityManager.UpdateAllEntities(window, deltaTime);


		// On présente la fenêtre sur l'écran
		window.display();
	}
}