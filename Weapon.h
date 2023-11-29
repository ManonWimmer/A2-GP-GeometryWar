#pragma once
#include <iostream>
#include <list>
#include "Projectile.h"


enum WeaponType
{
	Pistol,
	Rifle,
	Shotgun
};


class Weapon
{
public:
	Weapon(WeaponType, sf::CircleShape&);
	void Shoot(sf::RenderWindow&, sf::Vector2f);
	void CheckProjectiles(sf::RenderWindow&, float);
	void CheckRotationAim(sf::RectangleShape&, sf::RenderWindow&);
	std::list<Projectile*> WeaponPtrProjectiles;
	int FireTime;
	float FireRate;
	sf::CircleShape Player;
	
private:
	int _bulletSpeed;
	
};