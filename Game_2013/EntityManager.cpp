#include "EntityManager.h"
#include <iostream>

EntityManager *EntityManager::instance;

//Sort the entities so that they are in order by index
bool SortByIndex(BaseEntity *Ent1, BaseEntity *Ent2)
{
	return (Ent1->EntityIndex < Ent2->EntityIndex);
}

//Constructor
EntityManager::EntityManager()
{
}

//Deconstructor
EntityManager::~EntityManager()
{
}

//Get the end index of the list
unsigned int EntityManager::GetEndIndex()
{
	//Sort the list
	//std::sort(EntityList.begin(), EntityList.end(), SortByIndex);

	//Return the index of the entity at the end of the list
	//return EntityList[EntityList.size()-1]->EntityIndex;
	return 1;
}

//Draw all the entities in the list
void EntityManager::DrawEntities()
{
	//Set colour to be white
	glColor4f(1.0,1.0,1.0,1.0);

	//Loop through the list and draw each entity
	for (int i = 0; i < EntityList.size(); i++)
	{
		if (EntityList[i])
			EntityList[i]->Draw();
	}
}

//Update all the entities in the list
void EntityManager::UpdateEntities(float dt)
{
	//Sort the list
	//std::sort(EntityList.begin(), EntityList.end(), SortByIndex);

	//Move through the list
	//std::vector<BaseEntity*>::iterator it;
	//for (it = EntityList.begin(); it != EntityList.end();)
	//{
	//	BaseEntity *Ent = (*it);
	//	//If the entity is alive
	//	if (Ent->Live)
	//	{
	//		//Update it
	//		Ent->Update(dt);
	//
	//		//Increment the iterator
	//		it++;
	//	}
	//	//If the entity is not alive
	//	else
	//	{
	//		//Call the entity's delete function
	//		Ent->Delete();
	//		//Erase it
	//		//it = EntityList.erase(it);
	//	}
	//}
	for (int i = 0; i < EntityList.size();)
	{
		if (!EntityList[i])
		{
			i++;
		}
		else if (EntityList[i]->Live)
		{
			EntityList[i]->Update(dt);

			i++;
		}
		else
		{
			EntityList[i]->Delete();
			EntityList[i] = NULL;
			i++;
		}
	}
}

//Check the collision of all the entities
void EntityManager::CheckCollision()
{
	//If the entity list has more than one element
	if (EntityList.size() > 1)
	{
		//Loop through the entire list twice
		for (int i = 0; i < EntityList.size(); i++)
		{
			for (int k = 0; k < EntityList.size(); k++)
			{
				//Check collision if the entities are different
				if (i != k && EntityList[i] && EntityList[k])
					EntityList[i]->CollisionBox.checkCollision(&EntityList[k]->CollisionBox);
			}
		}
	}
}