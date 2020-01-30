#include "BoundingSphere.h"
#include "EntityManager.h"
//temp
#include <iostream>

//Default constructor
BoundingSphere::BoundingSphere(void)
{
	Collide = false;
	Radius = 0;
	Type = 0;
}

BoundingSphere::~BoundingSphere(void)
{
}

//Check collision
void BoundingSphere::checkCollision(BoundingSphere *sphere2)
{
	//If the two entities are friendlies, ignore this
	if (this->Type == sphere2->Type || this->Type == sphere2->Type + 2 || this->Type == sphere2->Type - 2)
		return;
	
	if ((this->Type == ItemDrop && sphere2->Type != Friend) || (this->Type != Friend && sphere2->Type == ItemDrop))
		return;

	if ((this->Type == FriendProjectile && sphere2->Type == FoeProjectile) || (this->Type == FoeProjectile && sphere2->Type == FriendProjectile))
		return;

	float distance;
	float radiusSum;
	
	//Sum of the radii
	radiusSum = Radius + sphere2->Radius;

	//Distance between the two entities
	distance = (*pos - *sphere2->pos).GetLengthSqr();

	//Check if the radii overlap
	if (distance <= (radiusSum * radiusSum))
	{
		//If the player has collided with an enemy, only collide the player
		if (this->Type == Friend && sphere2->Type == Foe)
			Collide = true;
		else if (this->Type == Foe && sphere2->Type == Friend)
			sphere2->Collide = true;
		else if (this->Type == ItemDrop && sphere2->Type == Friend)
			Collide = true;
		else if (this->Type == Friend && sphere2->Type == ItemDrop)
			sphere2->Collide = true;
		//If any other collision occurs, collide them both
		else
		{
			Collide = true;
			sphere2->Collide = true;
		}
	}

}

//Update the collision radius
void BoundingSphere::Update()
{
	//Set collision to false
	Collide = false;
}