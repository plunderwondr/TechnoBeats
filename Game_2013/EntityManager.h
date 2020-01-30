#pragma once

#include "BaseEntity.h"
#include <vector>

//Entity manager for the game, done as a singleton
class EntityManager
{
public:
	//Static function call to get the instance of the manager
	static EntityManager* GetInstance()
	{
		//If there is no instance, create a new one
		if (!instance)
			instance = new EntityManager();

		//return the instance
		return instance;
	}

	//Terminate the instance
	void Terminate()
	{
		//If the instance exists, delete it
		if(instance)
			instance->~EntityManager();
	}

	//Add a pointer to an entity to the list
	void AddEntity(BaseEntity *ent)
	{
		for (int i = 0; i < EntityList.size(); i++)
		{
			if (EntityList[i] == NULL)
			{
				ent->setIndex(i);
				EntityList[i] = ent;
				return;
			}
		}

		ent->setIndex(EntityList.size()-1);
		EntityList.push_back(ent);
	}

	//Delete an entity by index
	void DeleteEntity(unsigned int index)
	{
		//Move through the list
		std::vector<BaseEntity*>::iterator it;
		for (it = EntityList.begin(); it != EntityList.end();it++)
		{
			BaseEntity *Ent = (*it);
			//If the current entity has the same index as the one being searched, delete it
			if (Ent->EntityIndex == index)
			{
				//Call the entity's delete function
				Ent->Delete();
				//Erase it from the list
				it = EntityList.erase(it);
			}
		}
	}

	void DeleteAllEntities()
	{
		//Move through the list
		std::vector<BaseEntity*>::iterator it;
		for (it = EntityList.begin(); it != EntityList.end();it++)
		{
			BaseEntity *Ent = (*it);
			//Call the entity's delete function
			Ent->Delete();
			//Erase it from the list
			//it = EntityList.erase(it);
		}
		EntityList.clear();
	}

	//Get the index at the end of the list
	unsigned int GetEndIndex();

	//Draw all the entities
	void DrawEntities();

	//Update all the entities
	void UpdateEntities(float dt);

	//Check the collision of all the entities
	void CheckCollision();

private:
	//Constructor and deconstructor are private
	//Prevents multiple instances from being created
	EntityManager();
	~EntityManager();

	//List of all the entities
	std::vector<BaseEntity*> EntityList;

	//Static pointer to an EntityManager, this is the instance
	static EntityManager *instance;
};

