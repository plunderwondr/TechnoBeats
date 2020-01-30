#pragma once

#include "Vector.h"
#include "coordFrame.h"

#include "SFML\include\SFML\OpenGL.hpp"
#include "SFML\include\SFML\Graphics.hpp"
#include <string>

class Particle
{
public:
	//Constructors
	Particle(void);
	Particle(Vector3<float> position);
	Particle(Vector3<float> position, Vector3<float> velocity);
	Particle(Vector3<float> position, Vector3<float> velocity, Vector3<float> force);
	Particle(Vector3<float> position, Vector3<float> velocity, Vector3<float> force, Vector3<float> colour);
	~Particle(void);

	//Load the texture
	void LoadFile(std::string texFile);
	//Render the particle
	void Render();
	//Update the particle
	void Update(float dt);
	//Reset the particle
	void Reset();

	//Apply the force
	void ApplyForce(Vector3<float> Force)
	{
		//Set the force
		Force = Force;
		//Set the acceleration
		Acceleration = Force/Mass;
	}

	//Accelerate towards a point
	void AccelerateTowards(Vector3<float> Point, float accelMag)
	{
		//Set the movement type
		Movement = 1;
		//Set the target position
		TargetPointPosition = Point;
		//Set the acceleration magnitude
		AccelerationMagnitude = accelMag;
	}
	
	//Move along a path
	//Untested
	void MoveAlongPath(Vector3<float> Point, float accelMag)
	{
		//Set the movement type
		Movement = 2;
		//Set the target point
		TargetPointPosition = Point;
		//Set the acceleration magnitude
		AccelerationMagnitude = accelMag;
	}

	//Setters
	void SetInitialColour(Vector3<float> colour, float transparency)
	{
		InitialColour = colour;
		InitialTransparency = transparency;
	}

	void SetDecayColour(Vector3<float> colour, float transparency)
	{
		DecayColour = colour;
		DecayTransparency = transparency;
	}

	void SetPosition(Vector3<float> position)
	{
		Position = position;
	}
	void SetVelocity(Vector3<float> velocity)
	{
		Velocity = velocity;
	}
	void SetLife(float life)
	{
		Life = life;
		InitialLife = Life;
	}
	void SetMass(float mass)
	{
		Mass = mass;
	}
	void SetScale(float scale)
	{
		Scale = scale;
	}
	void SetMaxSpeed(float speed)
	{
		MaxSpeed = speed;
	}
	void SetShrinkRate(float rate)
	{
		ShrinkRate = rate;
	}
	void SetCoordFrame(coordFrame *frame)
	{
		Frame = frame;
	}

	//Getters
	Vector3<float> GetInitialColour()
	{
		return InitialColour;
	}
	float GetInitialTransparency()
	{
		return Transparency;
	}
	Vector3<float> GetDecayColour()
	{
		return DecayColour;
	}
	float GetDecayTransparency()
	{
		return DecayTransparency;
	}
	Vector3<float> GetPosition()
	{
		return Position;
	}
	Vector3<float> GetVelocity()
	{
		return Velocity;
	}
	float GetLife()
	{
		return Life;
	}
	float GetMass()
	{
		return Mass;
	}
	float GetScale()
	{
		return Scale;
	}
	float GetMaxSpeed()
	{
		return MaxSpeed;
	}
	float GetShrinkRate()
	{
		return ShrinkRate;
	}

	Particle operator+(const Particle &particle) const;
	Particle operator*(const float f) const;

	bool isAlive;

private:
	Vector3<float> InitialColour;
	Vector3<float> Colour;
	Vector3<float> DecayColour;
	float InitialTransparency;
	float Transparency;
	float DecayTransparency;

	Vector3<float> Position;
	Vector3<float> Velocity;
	Vector3<float> Acceleration;
	Vector3<float> Force;
	
	float Life;
	float InitialLife;
	float Mass;
	float MaxSpeed;
	float Scale;
	float ShrinkRate;

	int Movement; //1 = Target Point, 2 = Path. Otherwise, free run
	bool TargetPoint;
	Vector3<float> TargetPointPosition;
	float AccelerationMagnitude;

	unsigned int tex;

	coordFrame *Frame;
};

