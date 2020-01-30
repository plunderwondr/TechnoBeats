#pragma once

#include "Item.h"
#include "Vector.h"
#include <vector>

class ItemSpawner
{
public:

	//Static function call to get the instance of the manager
	static ItemSpawner* GetInstance()
	{
		//If there is no instance, create a new one
		if (!instance)
			instance = new ItemSpawner();

		//return the instance
		return instance;
	}

	void Terminate()
	{
		if (instance)
			delete instance;
	}

	void AddItem(Item itemObject);

	void SpawnItem(unsigned int itemSpawning, Vector3<float> spawnPosition);

	Item GetItem(unsigned int Item);

private:
	ItemSpawner();
	~ItemSpawner();

	std::vector<Item> itemList;

	static ItemSpawner *instance;
};