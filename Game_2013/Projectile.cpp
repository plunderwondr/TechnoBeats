#include "Projectile.h"
#include "ParticleManager.h"
#include "EntityManager.h"

#include <iostream>
Projectile::Projectile(void)
{
	//Set the projectile's index
	this->EntityIndex = EntityManager::GetInstance()->GetEndIndex();

	//Set the collision details
	CollisionBox.setRadius(1.0);
	CollisionBox.pos = &Position;

	//Set model to null
	model = NULL;

	Live = false;
}


Projectile::~Projectile(void)
{
	//Stop the particle effect when the projectile is destroyed
	particleEffect.Stop();
}

//Update the projectile
void Projectile::Update(float dt)
{
	
	//If the projectile has collided
	if (CollisionBox.Collide)
	{
		//Kill it
		Live = false;
		return;
	}
	
	//If the particle system has stopped running
	if (!particleEffect.Running)
	{
		//Kill it
		Live = false;
	}
	else
	{
		//Update the position
		Position += Velocity * dt;
		//testing stuff
		//std::cout<<Velocity.z * dt<<std::endl;

		//Set the position of the particle system
		particleEffect.SetPosition(Position);

		//Update the collision
		CollisionBox.Update();
	}
}

//Initialize the projectile
void Projectile::Initialize()
{
	//Add the projectile to the entity list
	EntityManager::GetInstance()->AddEntity(this);
	//Activate it
	Live = true;

	//Set the particle system's position
	particleEffect.SetPosition(Position);
	
	//Initialize it
	particleEffect.Initialize(200,10);
}