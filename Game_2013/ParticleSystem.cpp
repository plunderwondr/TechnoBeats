#include "ParticleSystem.h"
#include "ParticleManager.h"
#include <iostream>

float Random(float min, float max)
{
	return (float(rand()%3001)/3000.0f) * (max-min) + min;
}

ParticleSystem::ParticleSystem(void)
{
	//Set values to 0

	//Render times
	ParticlesPerSec = MaxParticles = NumberOfParticles = 0;

	//Radii for cylindrical or spherical volumes
	minRadius = maxRadius = 0;

	//Scale deviation
	scaleDeviation = 0.0f;

	//Effect
	//Explosion type
	ExplosionType = None;
	//Volume type
	VolumeType = Cube;

	//Animation
	RunType = Constant;

	//Running
	Running = false;

	RunTime = InitialRunTime = 0.0f;

}


ParticleSystem::~ParticleSystem(void)
{
}

//Render the particles of the system
void ParticleSystem::Render()
{
	//Create an iterator for the particles
	std::list<Particle*>::iterator it;
	//Run through the list of particles
	for (it = particles.begin(); it != particles.end();)
	{
		Particle *p = (*it);
		//If the particle is alive
		if (p->isAlive)
		{
			//Render the particle
			p->Render();
			//Increment
			it++;
		}
		//If the particle is not alive
		else
		{
			//Erase it
			it = particles.erase(it);
		}
	}
}

void ParticleSystem::Update(float dt)
{
	//Update the position of the system
	Position += Velocity * dt;
	
	//Create an iterator for the particles
	std::list<Particle*>::iterator it;
	//Move through the list
	for (it = particles.begin(); it != particles.end();)
	{
		Particle *p = (*it);
		//If the particle is alive
		if (p->isAlive)
		{
			//Update it with dt
			p->Update(dt);
			//Increment
			it++;
		}
		//If the particle is not alive
		else
		{
			//Erase it
			it = particles.erase(it);
		}
	}
	
	//Spawn particles
	SpawnParticles(dt);

	//Reset the run time, decrement the RunTime or kill the system
	if (RunType == Loop && RunTime <= 0.0f)
		ResetSystem();
	else if (RunType == Once && RunTime <= 0.0f)
		Running = false;
	else
		RunTime -= dt;
}

//Spawn particles based on the time between updates
void ParticleSystem::SpawnParticles(float dt)
{
	//If more particles can be spawned
	if (particles.size() < MaxParticles)
	{
		//Create a particle pointer
		Particle *tempPart = new Particle();

		//Loop through for the number of particles that can be spawned
		for (int i = 0; i < (ParticlesPerSec * dt);)
		{
			//Copy the information for the base particle
			*tempPart = Base;

			//Set the position for the temporary particle, creating it within the min-max areas to allow for a degree of randomness
			tempPart->SetPosition(Position + Vector3<>(Random(minSpawnRan.x, maxSpawnRan.x),
												 Random(minSpawnRan.y, maxSpawnRan.y),
												 Random(minSpawnRan.z, maxSpawnRan.z)));
			
			//Set the scale of the temporary particle, with deviations
			tempPart->SetScale(Random(tempPart->GetScale() - scaleDeviation, tempPart->GetScale() + scaleDeviation));
			
			//Set the life of the temporary particle, with deviations
			tempPart->SetLife(Random(tempPart->GetLife() - lifeRange, tempPart->GetLife() + lifeRange));

			//If the particle system is exploding
			if (ExplosionType == Explosion)	//Explode
			{
				//Set the velocity so the particles move away from the system
				tempPart->SetVelocity(((tempPart->GetPosition() - Position).Normalize()) * Random(0.00001,maxSpreadRan.GetLength()));
			}
			//If the particle system is set to implode
			else if (ExplosionType == Implosion) //Implode
			{
				//Set the velocity so the particles move closer to the system
				tempPart->SetVelocity(((tempPart->GetPosition() - Position).Normalize()) * (-1) * Random(0.00001,maxSpreadRan.GetLength()));
			}
			else
			{
				//Randomly generate a velocity based on the random spread
				tempPart->SetVelocity(Vector3<>(Random(minSpreadRan.x,maxSpreadRan.x), Random(minSpreadRan.y,maxSpreadRan.y), Random(minSpreadRan.z,maxSpreadRan.z)));
			}

			//Get the distance of the particle from the center of the system
			float distance = (tempPart->GetPosition() - Position).GetLength();

			//Check if the particle is within its boundaries
			if (VolumeType == Sphere && (distance >= minRadius && distance <= maxRadius))
			{
				//Add the particle to the list
				particles.push_back(tempPart);
				//Increment i
				++i;
			}
			else if (VolumeType == Cylinder)
			{
				//Set the distance for a cylindrical check
				distance = (Vector3<>(tempPart->GetPosition().x,0,tempPart->GetPosition().z) - Vector3<>(Position.x, 0, Position.z)).GetLength();

				//If the distance is within acceptable boundaries
				if (distance >= minRadius && distance <= maxRadius)
				{
					//Add the particle to the list
					particles.push_back(tempPart);
					++i;
				}
			}
			else if (VolumeType == Cube)
			{
				//Add the particle
				particles.push_back(tempPart);
				++i;
			}
			//i is only incremented if the particle is valid. If it is not, the loop is stuck at the current value until an acceptable particle is generated
		}
	}
}

//Reset the system
void ParticleSystem::ResetSystem()
{
	//Clear the list
	particles.clear();
	//Reset the timer
	RunTime = InitialRunTime;
}

//Load all the information for a particle system from a file
void ParticleSystem::LoadParticleFile(std::string particleFile)
{
	int fileEnd = 1;	//fileEnd, used for checking if we have reached the end of the file. Initialized to 1 to start the loop.
	char line[32];		//Char array, used for assigning values from the file stream
	FILE* system;	//FILE pointer, the stream for the obj file is assigned to this value so it can be read
	system = fopen(particleFile.c_str(), "rt");		//Open the stream and assign it to our FILE variable, uses the file sent in. "rt" makes it read-only text
	
	coordFrame *tempFrame = new coordFrame();
	Particle temp;
	Vector3<float> vecHolder;
	float floatHolder(0);
	char fileLink[32];

	//Loop while the program is not at the end of the file
	while (fileEnd != EOF)							
	{
		fileEnd = fscanf(system, "%s", line);	//Scan the file stream for a string, assign the first string encountered to the line variable (array of characters)
	
		//Check if the string is a v (vertex), vt (texture vertex), vn (normal vector)
		//or f (face).

		//If the string is v...
		if (strcmp(line, "SysPos:") == 0)
		{
			fscanf(system, "%f,%f,%f",&Position.x,&Position.y,&Position.z);	
		}
		else if (strcmp(line, "SysVel:") == 0)
		{
			fscanf(system, "%f,%f,%f",&Velocity.x,&Velocity.y,&Velocity.z);	
		}
		else if (strcmp(line, "SysSpreadMin:") == 0)
		{
			fscanf(system, "%f,%f,%f",&minSpreadRan.x,&minSpreadRan.y,&minSpreadRan.z);	
		}
		else if (strcmp(line, "SysSpreadMax:") == 0)
		{
			fscanf(system, "%f,%f,%f",&maxSpreadRan.x,&maxSpreadRan.y,&maxSpreadRan.z);	
		}
		else if (strcmp(line, "SysSpawnMin:") == 0)
		{
			fscanf(system, "%f,%f,%f",&minSpawnRan.x,&minSpawnRan.y,&minSpawnRan.z);	
		}
		else if (strcmp(line, "SysSpawnMax:") == 0)
		{
			fscanf(system, "%f,%f,%f",&maxSpawnRan.x,&maxSpawnRan.y,&maxSpawnRan.z);	
		}
		else if (strcmp(line, "SysLifeDev:") == 0)
		{
			fscanf(system, "%f",&lifeRange);	
		}
		else if (strcmp(line, "SysScaleDev:") == 0)
		{
			fscanf(system, "%f",&scaleDeviation);	
		}
		else if (strcmp(line, "SysVolume:") == 0)
		{
			fscanf(system, "%i",&VolumeType);	
		}
		else if (strcmp(line, "SysExplosion:") == 0)
		{
			fscanf(system, "%i",&ExplosionType);	
		}
		else if (strcmp(line, "SysRunType:") == 0)
		{
			fscanf(system, "%i",&RunType);	
		}
		else if (strcmp(line, "SysRunTime:") == 0)
		{
			fscanf(system, "%f",&InitialRunTime);	
		}
		else if (strcmp(line, "SysDir:") == 0)
		{
			fscanf(system, "%f,%f,%f",&tempFrame->Dir.x,&tempFrame->Dir.y,&tempFrame->Dir.z);	
		}
		else if (strcmp(line, "SysRight:") == 0)
		{
			fscanf(system, "%f,%f,%f",&tempFrame->Right.x,&tempFrame->Right.y,&tempFrame->Right.z);	
		}
		else if (strcmp(line, "PartInitCol:") == 0)
		{
			fscanf(system, "%f,%f,%f,%f",&vecHolder.x,&vecHolder.y,&vecHolder.z, &floatHolder);

			temp.SetInitialColour(vecHolder, floatHolder);
		}
		else if (strcmp(line, "PartDecaCol:") == 0)
		{
			fscanf(system, "%f,%f,%f,%f",&vecHolder.x,&vecHolder.y,&vecHolder.z, &floatHolder);

			temp.SetDecayColour(vecHolder, floatHolder);
		}
		else if (strcmp(line, "PartLife:") == 0)
		{
			fscanf(system, "%f",&floatHolder);

			temp.SetLife(floatHolder);
		}
		else if (strcmp(line, "PartMaxSpeed:") == 0)
		{
			fscanf(system, "%f",&floatHolder);

			temp.SetMaxSpeed(floatHolder);
		}
		else if (strcmp(line, "PartMass:") == 0)
		{
			fscanf(system, "%f",&floatHolder);

			temp.SetMass(floatHolder);
		}
		else if (strcmp(line, "PartScale:") == 0)
		{
			fscanf(system, "%f",&floatHolder);

			temp.SetScale(floatHolder);
		}
		else if (strcmp(line, "PartShrink:") == 0)
		{
			fscanf(system, "%f",&floatHolder);

			temp.SetShrinkRate(floatHolder);
		}
		else if (strcmp(line, "PartApplyForce:") == 0)
		{
			fscanf(system, "%f,%f,%f",&vecHolder.x,&vecHolder.y,&vecHolder.z);

			temp.ApplyForce(vecHolder);
		}
		else if (strcmp(line, "PartFile:") == 0)
		{
			fscanf(system, "%s",&fileLink);

			temp.LoadFile(fileLink);
		}
	}
	
	tempFrame->calcUp();

	temp.SetCoordFrame(tempFrame);

	SetBaseParticle(temp);

	fclose(system);						//Close the stream...VERY IMPORTANT
}

//Initialize the system
void ParticleSystem::Initialize(int numOfParticles, float partPerSec)
{
	//Set the max number of particles
	MaxParticles = numOfParticles;
	//Set the particles spawned per second
	ParticlesPerSec = partPerSec;
	//Set the run time
	RunTime = InitialRunTime;
	//Set running
	Running = true;

	//Add to the particle manager
	ParticleManager::GetInstance()->AddSystem(this);
}

////////////////////////////////////////////////////
//Modify - Meant to allow for Paths with Particles//
//Problem: Maintaining the list of particles	  //
////////////////////////////////////////////////////
ParticleSystem ParticleSystem::operator+(const ParticleSystem &particleSystem) const
{
	ParticleSystem temp;

	if (this->ExplosionType == particleSystem.ExplosionType &&
		this->VolumeType == particleSystem.VolumeType &&
		this->RunType == particleSystem.RunType &&
		this->RunType != Once && particleSystem.RunType != Once)

	{
		temp.Position = this->Position + particleSystem.Position;

		temp.minSpreadRan = this->minSpreadRan + particleSystem.minSpreadRan;
		temp.maxSpreadRan = this->maxSpreadRan + particleSystem.maxSpreadRan;

		temp.minSpawnRan = this->minSpawnRan + particleSystem.minSpawnRan;
		temp.maxSpawnRan = this->maxSpawnRan + particleSystem.maxSpawnRan;

		temp.lifeRange = this->lifeRange + particleSystem.lifeRange;

		temp.scaleDeviation = this->scaleDeviation + particleSystem.scaleDeviation;

		temp.maxRadius = this->maxRadius + particleSystem.maxRadius;
		temp.maxRadius = this->maxRadius + particleSystem.maxRadius;

		temp.ParticlesPerSec = this->ParticlesPerSec + particleSystem.ParticlesPerSec;

		temp.MaxParticles = this->MaxParticles + particleSystem.MaxParticles;

		temp.Base = this->Base + particleSystem.Base;
	}

	temp.Running = true;

	return temp;
}

ParticleSystem ParticleSystem::operator*(const float f) const
{
	ParticleSystem temp;

	temp.Position = this->Position * f;

	temp.minSpreadRan = this->minSpreadRan * f;
	temp.maxSpreadRan = this->maxSpreadRan * f;

	temp.minSpawnRan = this->minSpawnRan * f;
	temp.maxSpawnRan = this->maxSpawnRan * f;

	temp.lifeRange = this->lifeRange * f;

	temp.scaleDeviation = this->scaleDeviation * f;

	temp.maxRadius = this->maxRadius * f;
	temp.maxRadius = this->maxRadius * f;

	temp.ParticlesPerSec = this->ParticlesPerSec * f;

	temp.MaxParticles = this->MaxParticles * f;

	temp.Base = this->Base * f;

	return temp;
}