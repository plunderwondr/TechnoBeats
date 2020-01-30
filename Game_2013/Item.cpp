#include "Item.h"
#include "MessageRelay.h"

Item::Item()
{
	DropType = 0;
	LifeTime = 5.0f;
}

Item::~Item()
{
}

void Item::SpawnItem()
{
	Live = true;
	CollisionBox.pos = &Position;
	EntityManager::GetInstance()->AddEntity(this);
	time = 0.0f;
}

void Item::Update(float dt)
{
	extern bool HaveTripple;
	if (CollisionBox.Collide)
	{
		//Kill it
		MessageRelay::GetInstance()->ActivateAbility(DropType);
 		Live = false;
		HaveTripple = true;
	}

	time += dt;

	if (time >= LifeTime)
		Live = false;
}