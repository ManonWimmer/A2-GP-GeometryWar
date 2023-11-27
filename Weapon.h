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
	Weapon(WeaponType, sf::RectangleShape);
	void Shoot();
	void CheckProjectiles();

private:
	int _fireRate, _bulletSpeed, _fireTime;
	std::list<Projectile*> _weaponPtrProjectiles;
	sf::RectangleShape _rectangle;
};