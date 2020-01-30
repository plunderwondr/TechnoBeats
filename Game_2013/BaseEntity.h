#pragma once

#include "Model.h"
#include "Animation.h"
#include "Vector.h"
#include "coordFrame.h"
#include "BoundingSphere.h"

#include <string>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class BaseEntity
{
public:
	BaseEntity(void);
	~BaseEntity(void);

	//Delete the entity
	virtual void Delete()
	{
		//Call deconstructor
		this->~BaseEntity();
		//Room for unique death effects
	}

	//Set Position
	void setPosition(Vector3<float> pos)
	{
		//Set the position of the entity
		Position = pos;
		//std::cout << "vv" ;// Position ;
	}


	//Set Velocity
	void setVelocity(Vector3<float> vel)
	{
		//Set the velocity of the entity
		Velocity = vel;
	}

	//Set Orientation
	void setOrientation(Vector3<float> ori)
	{
		ori.Normalize();
		//Set the orientation of the entity
		Orientation = ori;
		EntityFrame.Dir = ori;
	}

	//Set speed
	void setSpeed(float s)
	{
		//Set the speed of the entity
		Speed = s;
	}

	void setIndex(int index)
	{
		EntityIndex = index;
		CollisionBox.CollisionIndex = index;
	}
	//Add animation
	void addAnimation(Animation anim)
	{
		//Add an animation to the list
		animations.push_back(anim);
	}

	//Set Current Animation
	virtual void setAnimation(int animation)
	{
		currentAnimation = animation;
	}

	//Draw the entity
	virtual void Draw()
	{
		//If there is no model, return
		if (model == NULL)
			return;

		float angle;

		angle = acos(Orientation.Normalize().Dot(Vector3<float>(1.0,0.0,0.0)));

		angle = angle * (180.0/M_PI);
		
		glPushMatrix();
		

		//Translate to the proper position
		glTranslatef(Position.x, Position.y, Position.z);
		
		glRotatef(angle,0.0,1.0,0.0);

		//Draw the model
		model->readObject();

		glPopMatrix();
	}

	//Update the model
	virtual void Update(float dt);
	
	unsigned int EntityIndex;

	coordFrame EntityFrame;

	BoundingSphere CollisionBox;

	std::string name;

	bool Live;

	Vector3<float> Position;
	Vector3<float> Orientation;	//Convert to a Quaternion at some point
	Vector3<float> Velocity;
	float Speed;
	int type;

	unsigned int currentAnimation;

	std::vector<Animation> animations;
	Model *model;
};

