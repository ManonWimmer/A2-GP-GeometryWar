#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "ManagerEntity.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "GameManager.h"
#include "Weapon.h"
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
	GameManager gameManager(entityManager, collisionDetection, player);

	entityManager.AddEntity(&player);

	//entityManager.DebugEntities(entityManager, collisionDetection, player);

	gameManager.StartLevel(1);
	

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

		std::list<AI_Agent*>::iterator it = gameManager._enemies.begin();
		while (it != gameManager._enemies.end())
		{
			collisionDetection.BulletsTouchEnemyCheck(*(*it), (*player.ptrPistol));
			it++;
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}