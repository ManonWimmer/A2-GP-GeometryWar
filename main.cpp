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

	entityManager.DebugEntities(entityManager, collisionDetection, player);

	gameManager.StartLevel(1);




	Weapon* ptrPistol = new Weapon(WeaponType::Pistol, player.circleShape);

	bool shootPressed = false;
	float timeSinceLastShoot = 0;

	sf::RectangleShape aimRectangle;
	aimRectangle.setFillColor(sf::Color::White);
	aimRectangle.setPosition(640, 360);
	aimRectangle.setSize(sf::Vector2f(20, 50));
	aimRectangle.setOrigin(aimRectangle.getSize().x / 2, 0);



	

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


		ptrPistol->CheckProjectiles(window, deltaTime);
		window.draw(aimRectangle);

		aimRectangle.setPosition(player.circleShape.getPosition().x + player.circleShape.getRadius(), player.circleShape.getPosition().y + player.circleShape.getRadius());



		// Verif si il peut tirer (en fonction de fire rate)
		if (shootPressed)
		{
			timeSinceLastShoot += deltaTime;
			if (timeSinceLastShoot >= ptrPistol->FireRate)
			{
				shootPressed = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!shootPressed)
			{
				shootPressed = true;
				timeSinceLastShoot = 0;
				ptrPistol->Shoot(window, player.circleShape.getPosition());
			}
		}

		ptrPistol->CheckRotationAim(aimRectangle, window);

		// Affichage
		entityManager.UpdateAllEntities(window, deltaTime);

		std::list<AI_Agent*>::iterator it = gameManager._enemies.begin();
		while (it != gameManager._enemies.end())
		{
			collisionDetection.BulletsTouchEnemyCheck(*(*it), (*ptrPistol));
			it++;
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}