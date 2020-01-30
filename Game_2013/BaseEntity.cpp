#include "BaseEntity.h"

//Default constructor
BaseEntity::BaseEntity(void)
{
	//Set the default values to 0
	Orientation.setPosition(0.0f,0.0f,1.0f);
	Speed = 0.0f;
	currentAnimation = 0;

	CollisionBox.CollisionIndex = EntityIndex;
	CollisionBox.pos = &Position;

	Live = true;
}

BaseEntity::~BaseEntity(void)
{
}

void BaseEntity::Update(float dt)
{
	//Update the position of the entity
	Position += Velocity * dt;
	
	//Update the Collision box
	CollisionBox.Update();
	//model = animations[currentAnimation].getCurrent();
}