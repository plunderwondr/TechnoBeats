#pragma once

#include "Vector.h"
#include "coordFrame.h"
#include <vector>

//Enumerator for all the types of entities we will have
enum EntityType {Neutral, Friend, Foe, FriendProjectile, FoeProjectile, ItemDrop};

//Collision radius for the entities
class BoundingSphere
{
public:
	BoundingSphere(void);
	~BoundingSphere(void);

	//Update
	void Update();

	//Check the Collision between two entities
	void checkCollision(BoundingSphere *sphere2);

	//Set the collision radius
	void setRadius (float radius)
	{
		Radius = radius;
	}

	//Pointer to a Vector so that the position stays constant with the entity
	Vector3<float> *pos;

	//Check radius
	float Radius;

	//Collision status
	bool Collide;

	//Index for the sphere
	unsigned int CollisionIndex;

	//Type of entity
	unsigned int Type;
};

