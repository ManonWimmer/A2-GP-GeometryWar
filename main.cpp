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
		entityManager.UpdateAllEntities(window, deltaTime);


		// On pr�sente la fen�tre sur l'�cran
		window.display();
	}
}