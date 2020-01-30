#pragma once

#include "ParticleSystem.h"

//Particle Manager
class ParticleManager
{
public:
	//Static function to get a pointer to the instance of the manager
	static ParticleManager* GetInstance()
	{
		//If no instance exists, create one
		if (!instance)
			instance = new ParticleManager();
		
		//Return the instance
		return instance;
	}

	//Terminate the instance
	void Terminate()
	{
		//If the instance exists, delete it
		if(instance)
			instance->~ParticleManager();
	}

	//Render each particle system in the list
	void renderSystems();

	//Update each particle system in the list based on the change in time
	void updateSystems(float dt);

	//Add a Particle System to the list
	void AddSystem(ParticleSystem system)
	{
		Systems.push_back(&system);
	}

	//Add a pointer to a Particle System to the list
	void AddSystem(ParticleSystem* system)
	{
		Systems.push_back(system);
	}

	void ClearSystems()
	{
		Systems.clear();
	}
	
private:
	ParticleManager(void);
	~ParticleManager(void);
	
	static ParticleManager *instance;
	std::list<ParticleSystem*> Systems;
};