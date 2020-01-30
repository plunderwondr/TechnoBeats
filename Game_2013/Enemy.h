#pragma once

#include "BaseEntity.h"
#include "Weapon.h"

#include <string>

#include <SFML\Window.hpp>



//Enemy Class
class Enemy: public BaseEntity
{
public:
	Enemy(void);
	~Enemy(void);
	
	void LoadStats(std::string statFile);

	//Delete
	virtual void Delete();

	//Spawn a new enemy
	void NewEnemy(Vector3<float> spawnPosition);
	void NewEnemy(Vector3<float> spawnPosition, Vector3<float> spawnOrientation);

	//Update the enemy
	virtual void Update(float dt);

	//Fire weapons
	void Fire();

	Weapon EnemyWeapon;

private:
	sf::Time fireDelay;
	sf::Clock shooterTime;
};
