#pragma once

/* 
Things to do:
-Memory management
-Path Traversal for Particles
-Rotation and Rotation around point
*/

enum TypeOfExplosion {Explosion, Implosion, None};
enum TypeOfRun {Once, Loop, Constant};
enum TypeOfVolume {Cube, Sphere, Cylinder};

#include "Particle.h"
#include "Vector.h"
#include <list>

class ParticleSystem
{
public:
	//Functions
	ParticleSystem(void);
	~ParticleSystem(void);

	//Run time operations
	void Render();						//Render the particles in the system
	void Update(float dt);				//Update the particles in the system
	void SpawnParticles(float dt);		//Spawn a new series of particles
	void ResetSystem();					//Reset the system

	//////////////////////Set FX\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	
	//Set the volume type of the system. Default is false (square volume)
	void SetVolume(int volume)
	{
		if (volume == 1)
			VolumeType = Sphere;
		else if (volume = 2)
			VolumeType = Cylinder;
		else
			VolumeType = Cube;
	}
	
	//Set the explosion type of the system. Default for the ExplosionType is 0 (no explosion effect)
	void SetExplosion(int explosion)
	{
		if (explosion == 1)
			ExplosionType = Explosion;
		else if (explosion == 2)
			ExplosionType = Implosion;
		else
			ExplosionType = None;

		//ExplosionType = explosion;						//Assign the sent in value to the ExplosionType variable
	}

	void SetRunType(int run)
	{
		if (run == 0)
			RunType = Once;
		else if (run == 1)
			RunType = Loop;
		else
			RunType = Constant;
	}

	//Load Particle Data from a file
	void LoadParticleFile(std::string particleFile);

	//Initialize the particle system
	void Initialize(int numOfParticles, float partPerSec);
	

	//Set the Position of the System. By default it is [0,0,0]
	void SetPosition(Vector3<float> pos)
	{
		Position = pos;
	}

	//Set the Velocity of the System. By default it is [0,0,0]
	void SetVelocity(Vector3<float> vel)
	{
		Velocity = vel;
	}

	///////////////Setters\\\\\\\\\\\\\\\\\\\
	//Set the Scale Deviation. The default value is 0
	void SetScaleDeviation(float deviation)
	{
		scaleDeviation = deviation;
	}

	//Set the Life Deviation. Default value is 0
	void SetLifeDeviation(float deviation)
	{
		lifeRange = deviation;
	}

	//Set the Minumum Radius and the Maximum Radius. Their default values are 0.
	void SetRadii(float min, float max)
	{
		minRadius = min;
		maxRadius = max;
	}

	//Set the Minimum and Maximum Spread Deviations (initial velocity)
	//By default these two 3D Vectors are [0,0,0]
	void SetSpreadDeviation(Vector3<float> min, Vector3<float> max)
	{
		minSpreadRan = min;
		maxSpreadRan = max;
	}

	//Set the Minimum and Maximum Spawn Deviations (initial position)
	//By default these two 3D Vectors are [0,0,0]
	void SetSpawnDeviation(Vector3<float> min, Vector3<float> max)
	{
		minSpawnRan = min;
		maxSpawnRan = max;
	}

	//Set the InitialRunTime of the System. By default it is 0
	void SetRunTimes(float run)
	{
		InitialRunTime = run;
	}

	//Set the Base particle of the System
	void SetBaseParticle(Particle part)
	{
		Base = part;
	}

	void Stop()
	{
		Running = false;
	}

	ParticleSystem operator+(const ParticleSystem &particleSystem) const;
	ParticleSystem operator*(const float f) const;
	
	//Runtime variable
	bool Running;

	//Members
private:
	//Particle System Position
	Vector3<float> Position;
	Vector3<float> Velocity;

	//For random spread
	Vector3<float> minSpreadRan;
	Vector3<float> maxSpreadRan;
	
	//For random spawn
	Vector3<float> minSpawnRan;
	Vector3<float> maxSpawnRan;

	//Deviations
	float lifeRange;
	float scaleDeviation;

	//Spawn radius for Radial
	float minRadius;
	float maxRadius;

	//Particle List
	std::list<Particle*> particles;
	//Particle *particleList;

	//The base particle
	Particle Base;

	//System variables
	float ParticlesPerSec;
	unsigned int MaxParticles;
	unsigned int NumberOfParticles;

	//FX variables
	TypeOfVolume VolumeType;
	TypeOfExplosion ExplosionType;
	
	//Run-type
	TypeOfRun RunType;

	//Runtime variables
	float RunTime;
	float InitialRunTime;
};

