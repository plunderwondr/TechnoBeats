#pragma once

#include "Projectile.h"
#include "Vector.h"
#include "coordFrame.h"
#include "ParticleSystem.h"

//Enumerator for the type of firing behaviours
enum FireType {SingleShot, ScatterShot, Missile, Beam};

//Weapon class
class Weapon
{
public:
	Weapon(void);
	~Weapon(void);

	//Fire the weapon
	void FireWeapon(Vector3<float> spawnPoint, unsigned int damageType, coordFrame frame, unsigned int friendOrFoe);

	float damage;
	unsigned int fireType;
	float speed;

	//Particle system for the projectiles
	ParticleSystem VisualFX;
};

