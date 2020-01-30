#pragma once

#include "BaseEntity.h"
#include "ParticleManager.h"

//Projectile class
class Projectile: public BaseEntity
{
public:
	Projectile(void);
	~Projectile(void);
	
	//Delete the projectile
	virtual void Delete()
	{
		//Call deconstructor
		this->~Projectile();
	}

	//Update the projectile
	virtual void Update(float dt);

	//Initialize the projectile
	void Initialize();

	//Hold the particle system for the projectile
	ParticleSystem particleEffect;

	//Projectile variables
	float Damage;
	unsigned int Type;
};

