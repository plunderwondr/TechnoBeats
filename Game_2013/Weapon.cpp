#include "Weapon.h"
#include "Quaternion.h"
#include <iostream>

//Default constructor
Weapon::Weapon(void)
{
	//Set values to 0
	damage = 0;
	fireType = 0;
	speed = 0;
}

Weapon::~Weapon(void)
{
}

//Fire the weapon with a spawn point, damage type, coordinate frame,
//and IFF
void Weapon::FireWeapon(Vector3<float> spawnPoint, unsigned int damageType, coordFrame frame, unsigned int friendOrFoe)
{
	//If the fire type is a single shot
	if (fireType == SingleShot)
	{
		//Get the velocity
		Vector3<float> Velocity = frame.Dir * speed;

		//Create a new projectile
		//Set all its variables
		Projectile *tempProjectile = new Projectile();
		tempProjectile->particleEffect = VisualFX;
		tempProjectile->EntityFrame = frame;
		tempProjectile->Position = spawnPoint;
		tempProjectile->Type = damageType;
		tempProjectile->setVelocity(Velocity);

		tempProjectile->CollisionBox.Type = (friendOrFoe + 2);

		//Initialize the projectile
		tempProjectile->Initialize();
	}
	//If the fire type is a scatter shot
	else if (fireType == ScatterShot)
	{
		//Same as above, rotate the velocity by x degrees
		//For loop from -1 to 1, Velocity = frame.dir rotated by x * i

		//Same as above, done 3 times with 2 rotations, change for a for loop
		Vector3<float> Velocity;
		Velocity = frame.Dir * speed;

		Projectile *tempProjectile = new Projectile();
		tempProjectile->particleEffect = VisualFX;
		tempProjectile->particleEffect.Initialize(200,10);
		tempProjectile->EntityFrame = frame;
		tempProjectile->Position = spawnPoint;
		tempProjectile->Type = damageType;
		tempProjectile->setVelocity(Velocity);

		tempProjectile->CollisionBox.Type = (friendOrFoe + 2);

		tempProjectile->Initialize();
		
		Quaternion quat(10,Vector3<float>(0.0,1.0,0.0));
		Velocity = quat.RotateVector(frame.Dir);
		Velocity = Velocity * -speed;

		tempProjectile = new Projectile();
		tempProjectile->particleEffect = VisualFX;
		tempProjectile->particleEffect.Initialize(200,10);
		tempProjectile->EntityFrame = frame;
		tempProjectile->Position = spawnPoint;
		tempProjectile->Type = damageType;
		tempProjectile->setVelocity(Velocity);

		tempProjectile->CollisionBox.Type = (friendOrFoe + 2);

		tempProjectile->Initialize();
		
		Quaternion quat2(-10,Vector3<float>(0.0,1.0,0.0));
		Velocity = quat2.RotateVector(frame.Dir);
		Velocity = Velocity * -speed;

		tempProjectile = new Projectile();
		tempProjectile->particleEffect = VisualFX;
		tempProjectile->particleEffect.Initialize(200,10);
		tempProjectile->EntityFrame = frame;
		tempProjectile->Position = spawnPoint;
		tempProjectile->Type = damageType;
		tempProjectile->setVelocity(Velocity);

		tempProjectile->CollisionBox.Type = (friendOrFoe + 2);

		tempProjectile->Initialize();
	}
	//Currently unused
	else if (fireType == Missile)
	{
	}
	//Currently unused
	else if (fireType == Beam)
	{
	}
}
