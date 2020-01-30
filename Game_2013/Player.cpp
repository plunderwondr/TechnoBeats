#include "Player.h"
#include <iostream>

//Default constructor
Player::Player(void)
{
	userInput.Up = 
	userInput.Left =
	userInput.Down =
	userInput.Right = 
	userInput.Space = false;


	Speed = 50.0f;
	EntityIndex = 1;

	CollisionBox.pos = &Position;
	//Un-hard code later
	CollisionBox.setRadius(5.0);

	CollisionBox.Type = Friend;

	Live = true;

	currentWeapon = 0;
	currentType = 0;

	LoadWeapons();

	//Create 2 weapons for testing purposes
	Weapon tempWep;
	
	ParticleSystem *test = new ParticleSystem();
	test->SetPosition(Vector3<float>(Position));
	test->SetVelocity(Vector3<>(0.0, 0.0, 0.0));
	test->SetSpreadDeviation(Vector3<>(-1.5f,0.0f,-1.5f),Vector3<>(1.5f,0.0f,1.5f));
	test->SetSpawnDeviation(Vector3<>(),Vector3<>());
	test->SetLifeDeviation(0.1f);
	test->SetScaleDeviation(0.3f);
	test->SetExplosion(0);
	test->SetRunType(0);
	test->SetRunTimes(10);

	coordFrame *tempFrame = new coordFrame;
	tempFrame->setDir(Vector3<>(0.0,1.0,0.0));
	tempFrame->setRight(Vector3<>(1.0,0.0,0.0));
	tempFrame->calcUp();

	////Particle
	Particle temp;
	temp.SetCoordFrame(tempFrame);
	temp.SetInitialColour(Vector3<>(1.0,0.0,0.0),1.0f);
	temp.SetDecayColour(Vector3<>(1.0,0.5,0.5),0.6f);
	temp.SetLife(0.3f);
	temp.SetMaxSpeed(1000);
	temp.SetMass(1.0f);
	temp.SetScale(1.0f);
	temp.SetShrinkRate(0.001f);
	temp.ApplyForce(Vector3<>(0.0,0.0f,0.0f));
	temp.LoadFile("Particle/LaserParticle.png");

	test->SetBaseParticle(temp);

	tempWep.VisualFX = *test;
	tempWep.damage = 5.0f;
	tempWep.speed = 50.0f;
	tempWep.fireType = SingleShot;
	Arsenal.push_back(tempWep);

	tempWep.fireType = ScatterShot;
	Arsenal.push_back(tempWep);

	temp.SetInitialColour(Vector3<>(0.0,0.0,1.0),1.0f);
	temp.SetDecayColour(Vector3<>(0.5,0.5,1.0),0.6f);

	test->SetBaseParticle(temp);
	tempWep.VisualFX = *test;

	tempWep.fireType = SingleShot;
	Arsenal.push_back(tempWep);

	tempWep.fireType = ScatterShot;
	Arsenal.push_back(tempWep);

	temp.SetInitialColour(Vector3<>(1.0,1.0,0.0),1.0f);
	temp.SetDecayColour(Vector3<>(1.0,1.0,0.5),0.6f);

	test->SetBaseParticle(temp);
	tempWep.VisualFX = *test;

	tempWep.fireType = SingleShot;
	Arsenal.push_back(tempWep);

	tempWep.fireType = ScatterShot;
	Arsenal.push_back(tempWep);
}


Player::~Player(void)
{
}

void Player::LoadWeapons()
{
}

//Update the player
void Player::Update(float dt)
{
	//Get any activated abilities
	int ability = MessageRelay::GetInstance()->PlayerMessage();

	if (ability > 0 && HeldItem.size() < 5)
	{
		HeldItem.push_back(ability);
	}

	//Recalculate the player frame
	EntityFrame.recalc();
	extern int Health;
	extern int Sheild;
	extern int HitDelay;
	extern float JamMeter;
	extern float LevelTimer;
	extern bool HaveTripple;

	if(HitDelay > 0)
	{
		HitDelay = HitDelay - 1;
	}
	//If the player has not collided
	if (!CollisionBox.Collide)
	{
		//Move them in a direction relative to their coordinate frame and what key they're pressing
		if (userInput.Up && Position.z > -62.0)
		{
			Position.x += EntityFrame.Dir.x * (Speed*dt);
			Position.z += EntityFrame.Dir.z * (Speed*dt);
		}
		if (userInput.Left && Position.x > -62.0)
		{
			Position.x -= EntityFrame.Right.x * (Speed*dt);
			Position.z -= EntityFrame.Right.z * (Speed*dt);
		}
		if (userInput.Down && Position.z < 62.0)
		{
			Position.x -= EntityFrame.Dir.x * (Speed*dt);
			Position.z -= EntityFrame.Dir.z * (Speed*dt);
		}
		if (userInput.Right && Position.x < 62.0)
		{
			Position.x += EntityFrame.Right.x * (Speed*dt);
			Position.z += EntityFrame.Right.z * (Speed*dt);
		}
	}
	else
	{
		if(HitDelay == 0)
		{
			if(JamMeter == 0)
			{
			
					if(Sheild == 0)
					{
						if(Health > 0)
						{
							Health = Health - 2;
						}
						else
						{
							Health = 10;
							Sheild = 10;
							JamMeter = 0;
							LevelTimer = 0;
							HaveTripple = false;
							MessageRelay::GetInstance()->ReturnToMenu();

						}
					}
					else
					{
						Sheild = Sheild -2;
					}

			}
			else if(JamMeter <= 1)
			{
				JamMeter = 0;
			}
			else
			{
				JamMeter = JamMeter -2;
			}
			HitDelay = 300;
		}


	}

	//Update collision box
	CollisionBox.Update();
	//MessageRelay::GetInstance()->ResetPlayer();
}

//Fire player's current weapon
void Player::Fire()
{
	//Check fire delay
	fireDelay = shooterTime.getElapsedTime();

	float time = fireDelay.asSeconds();

	//If enough time has passed
	if (time > 0.25f)
	{
		//Restart timer
		shooterTime.restart();
	
		//Fire current weapon
		Arsenal[(2*currentType) + currentWeapon].FireWeapon(Position, currentType, EntityFrame, 1);
	}
}