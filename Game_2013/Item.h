#pragma once

#include "BaseEntity.h"
#include "EntityManager.h"
#include "Vector.h"
#include <SFML\Window.hpp>

//enum ItemType {None, Rapid, Missile, Beam, Combo, Scatter, Piercing, Mortar, Speed, Multi};

class Item: public BaseEntity
{
public:
	Item(void);
	~Item(void);

	void SpawnItem();

	virtual void Update(float dt);

	unsigned int DropType;

	float time;
	float LifeTime;
};