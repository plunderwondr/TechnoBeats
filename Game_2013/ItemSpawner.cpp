#include "ItemSpawner.h"

ItemSpawner *ItemSpawner::instance;

ItemSpawner::ItemSpawner()
{
}

ItemSpawner::~ItemSpawner()
{
}

void ItemSpawner::AddItem(Item itemObject)
{
	itemList.push_back(itemObject);
}

void ItemSpawner::SpawnItem(unsigned int itemSpawning, Vector3<float> spawnPosition)
{
	if (itemSpawning >= itemList.size())
		return;

	Item *newItem = new Item();
	*newItem = itemList[itemSpawning];
	newItem->setPosition(spawnPosition);

	newItem->SpawnItem();
}