#include "ParticleManager.h"

ParticleManager *ParticleManager::instance;

ParticleManager::ParticleManager(void)
{
}


ParticleManager::~ParticleManager(void)
{
}

//Render the particle systems
void ParticleManager::renderSystems()
{
	//Create an iterator for the Particle Systems
	std::list<ParticleSystem*>::iterator it;

	//Move through the list of Systems
 	for (it = Systems.begin(); it != Systems.end();)
	{
		ParticleSystem *p = (*it);
		//If the system is running
		if (p->Running)
		{
			//Draw the system
			p->Render();
			//Increment the iterator
			it++;
		}
		//If the system is not running
		else
		{
			///Erase the system from the list
			it = Systems.erase(it);
		}
	}
}

//Update the particle systems
void ParticleManager::updateSystems(float dt)
{
	//Iterator for the list
	std::list<ParticleSystem*>::iterator it;
	
	//Move through the list of systems
	for (it = Systems.begin(); it != Systems.end();)
	{
		ParticleSystem *p = (*it);
		//If the system is running
		if (p->Running)
		{
			//Update the particle system
			p->Update(dt);
			//Increment the iterator
			it++;
		}
		//If the system is not running
		else
		{
			//Erase the system from the list
			it = Systems.erase(it);
		}
	}
}
