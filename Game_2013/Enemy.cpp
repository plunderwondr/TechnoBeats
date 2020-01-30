#include "Enemy.h"
#include "Game.h"
#include "EntityManager.h"
#include "MessageRelay.h"
#include "Projectile.h"
#include "ItemSpawner.h"
#include <iostream>
#include "QuickBeats.h"


//Default constructor
Enemy::Enemy(void)
{
	
	Speed = 10.0f;
	type = 0;
	//Set Collision Type
	CollisionBox.Type = Foe;
}

//Default deconstructor
Enemy::~Enemy(void)
{
}

void Enemy::LoadStats(std::string statFile)
{
	int fileEnd = 1;
	char line[32];
	FILE* stats;
	stats = fopen(statFile.c_str(), "rt");

	unsigned int intHolder(0);
	float floatHolder(0);
	char fileLink[32];

	while (fileEnd != EOF)
	{
		fileEnd = fscanf(stats, "%s", line);

		if (strcmp(line, "Speed:") == 0)
		{
			fscanf(stats, "%f", &floatHolder);

			Speed = floatHolder;
		}
		if (strcmp(line, "Type:") == 0)
		{
			fscanf(stats, "%f", &floatHolder);

			type = floatHolder;
		}
		else if (strcmp(line, "Radius:") == 0)
		{
			fscanf(stats, "%f", &floatHolder);

			CollisionBox.Radius = floatHolder;
		}
		else if (strcmp(line, "FireType:") == 0)
		{
			fscanf(stats, "%i", &intHolder);

			EnemyWeapon.fireType = intHolder;
		}
		else if (strcmp(line, "FireSpeed:") == 0)
		{
			fscanf(stats, "%f", &floatHolder);

			EnemyWeapon.speed = floatHolder;
		}
		else if (strcmp(line, "Damage:") == 0)
		{
			fscanf(stats, "%f", &floatHolder);

			EnemyWeapon.damage = floatHolder;
		}
		else if (strcmp(line, "ParticleSystem:") == 0)
		{
			fscanf(stats, "%s", &fileLink);

			EnemyWeapon.VisualFX.LoadParticleFile(fileLink);
		}
	}

	fclose(stats);
}

//Update the enemy
void Enemy::Update(float dt)
{
	EntityFrame.recalc();
	extern int TheScore;
	extern float JamMeter;
	extern int weaptype;
	//extern Player player;
	//If the enemy has collided
	if (CollisionBox.Collide)
	{
		std::cout<< weaptype <<std::endl;

		//Kill it
		if(this->type == weaptype)
		{
 		Live = false;
		//Reward points
		
		//QuickBeats.TheScore++
		if(JamMeter>=9)
		{
			JamMeter = 10;
		}
		else 
		{
			JamMeter++;
		}

		TheScore = TheScore + 10;
		//std::cout << TheScore << "\n";

		//Spawn item
		ItemSpawner::GetInstance()->SpawnItem(0, Position);
		}
	}
	else if (Position.z > 70.0)
	{
		//Has gone off screen
		Live = false;
	}

	//Update the position
	Position += (Orientation * Speed) * dt;

	//Check the fire delay
	fireDelay = shooterTime.getElapsedTime();

	//If enough time has passed
	if (fireDelay.asSeconds() > 2.0f)
	{
		//Fire
		Fire();
	}
}

//Create a new enemy at the spawned position
void Enemy::NewEnemy(Vector3<float> spawnPosition)
{
	//Create a new Enemy object
	Enemy *temp = new Enemy();
	//Give it all the values of the current enemy object
	*temp = *this;
	//Set its position to the spawn position
	temp->setPosition(spawnPosition);
	
	//Set its collision position
	temp->CollisionBox.pos = &temp->Position;

	//Get ready to remove
	//Set its collision radius
	temp->CollisionBox.setRadius (5.0);

	//Add it to the Entity List
	EntityManager::GetInstance()->AddEntity(temp);

	//Restart the shooter time
	shooterTime.restart();
}

//Create a new enemy at the spawned position
void Enemy::NewEnemy(Vector3<float> spawnPosition, Vector3<float> spawnOrientation)
{
	//Create a new Enemy object
	Enemy *temp = new Enemy();
	//Give it all the values of the current enemy object
	*temp = *this;
	//Set its position to the spawn position
	temp->setPosition(spawnPosition);
	//Set its position to the spawn position
	temp->setOrientation(spawnOrientation);
	
	//Set its collision position
	temp->CollisionBox.pos = &temp->Position;

	//Get ready to remove
	//Set its collision radius
	temp->CollisionBox.setRadius (5.0);

	//Add it to the Entity List
	EntityManager::GetInstance()->AddEntity(temp);

	//Restart the shooter time
	shooterTime.restart();
}

//Fire the enemy's weapon
void Enemy::Fire()
{
	//Restart the timer
	shooterTime.restart();
	
	//Try with event handler?
	EnemyWeapon.FireWeapon(Position,0,EntityFrame,2);
}

//Fix for explosion effect
//Execute with telegram system?
void Enemy::Delete()
{
	
	//std::cout<<"DING"<<std::endl;
	//ParticleSystem *test = new ParticleSystem();
	//test->SetPosition(Vector3<float>(Position));
	//test->SetVelocity(Vector3<>(0.0, 0.0, 0.0));
	//test->SetSpreadDeviation(Vector3<>(-1.5f,0.0f,-1.5f),Vector3<>(1.5f,0.0f,1.5f));
	//test->SetSpawnDeviation(Vector3<>(),Vector3<>());
	//test->SetLifeDeviation(0.5f);
	//test->SetScaleDeviation(0.3f);
	//test->SetExplosion(Explosion);
	//test->SetRunType(0);
	//test->SetRunTimes(10);
	//
	//coordFrame tempFrame;
	//tempFrame.setDir(Vector3<>(0.0,1.0,0.0));
	//tempFrame.setRight(Vector3<>(1.0,0.0,0.0));
	//tempFrame.calcUp();
	//
	////Particle
	//Particle temp;
	//temp.SetCoordFrame(&tempFrame);
	//temp.SetInitialColour(Vector3<>(1.0,0.3,1.0),1.0f);
	//temp.SetDecayColour(Vector3<>(0.0,1.0,1.0),0.6f);
	//temp.SetLife(0.5f);
	//temp.SetMaxSpeed(1000);
	//temp.SetMass(1.0f);
	//temp.SetScale(1.0f);
	//temp.SetShrinkRate(0.001f);
	//temp.ApplyForce(Vector3<>(0.0,0.0f,0.1f));
	//temp.LoadFile("Particle/test.png");
	//
	//test->Initialize(200,200);

	this->~Enemy();
}
