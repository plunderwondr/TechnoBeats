#include "Particle.h"
#include "AnimationMath.h"

//Default constructor
Particle::Particle(void)
{
	//Set all the values to defaults
	Life = Transparency = Mass = MaxSpeed = 0.0f;
	Scale = ShrinkRate = 1.0f;
	isAlive = true;
	TargetPoint = false;
	
}

//Construct with position
Particle::Particle(Vector3<float> position)
{
	//Set the position
	Position = position;
	//Set to defaults
	Life = Transparency = Mass = MaxSpeed = 0.0f;
	isAlive = true;
	TargetPoint = false;
}

//Construct with position and velocity
Particle::Particle(Vector3<float> position, Vector3<float> velocity)
{
	//Set position
	Position = position;
	//Set velocity
	Velocity = velocity;
	//Set to defaults
	Life = Transparency = Mass = MaxSpeed = 0.0f;
	isAlive = true;
	TargetPoint = false;
}

//Construct with position, velocity and force
Particle::Particle(Vector3<float> position, Vector3<float> velocity, Vector3<float> force)
{
	//Set position
	Position = position;
	//Set velocity
	Velocity = velocity;
	//Set force
	Force = force;
	//Set to defaults
	Life = Transparency = Mass = MaxSpeed = 0.0f;
	isAlive = true;
	TargetPoint = false;
}

//Construct with position, velocity, force and colour
Particle::Particle(Vector3<float> position, Vector3<float> velocity, Vector3<float> force, Vector3<float> colour)
{
	//Set the position
	Position = position;
	//Set the velocity
	Velocity = velocity;
	//Set the force
	Force = force;
	//Set the colour
	Colour = colour;
	//Set to defaults
	Life = Transparency = Mass = MaxSpeed = 0.0f;
	isAlive = true;
	TargetPoint = false;
}

Particle::~Particle(void)
{
}

//Load the particle image
void Particle::LoadFile(std::string texFile)
{
	sf::Image texImg;																														//Create a new Image

	if (!texImg.loadFromFile(texFile.c_str()))																								//Open the image based on the file that is sent in	
		exit(1);																															//End the program if the game can not find the image
	
    glGenTextures(1, &tex);																													//Generate a new texture on the tex variable
    glBindTexture(GL_TEXTURE_2D, tex);																										//Bind the 2D texture to tex
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texImg.getSize().x, texImg.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, texImg.getPixelsPtr());	//Create the texture based on the image
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

//Draw the particle
void Particle::Render()
{
	//Check if the particle is alive, exit if it isn't
	if (!isAlive)
		return;

	//Create a temporary vector
	Vector3<float> tempV;

	//Enable and disable appropriate OpenGL functions
	glDepthMask(false);
	glDisable(GL_CULL_FACE);
	glEnable (GL_BLEND);
	glEnable(GL_ALPHA);

	//Set the colour
	glColor4f(Colour.x, Colour.y, Colour.z, Transparency);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glPushMatrix();

	//Move the particle
	glTranslatef(Position.x, Position.y, Position.z);

	//Draw the particle on a quad
	glBegin(GL_QUADS);
		//Set the temporary vertex based on the coordinate frame being used (should be camera) and the scale
		tempV = (Frame->Right * -Scale) - (Frame->Up * Scale);
		//Set texture coordinates
		glTexCoord2f(0.0f, 0.0f);
		//Draw vertex
		glVertex3f(tempV.x, tempV.y, tempV.z);
		
		//Ditto
		tempV = (Frame->Right * Scale) - (Frame->Up * Scale);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(tempV.x, tempV.y, tempV.z);
		
		tempV = (Frame->Right * Scale) + (Frame->Up * Scale);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(tempV.x, tempV.y, tempV.z);
		
		tempV = (Frame->Right * -Scale) + (Frame->Up * Scale);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(tempV.x, tempV.y, tempV.z);
	glEnd();

	glPopMatrix();

	//Change values back to normal
	glDepthMask(true);
	glEnable(GL_CULL_FACE);
	glDisable (GL_BLEND);
	glDisable(GL_ALPHA);
}

//Update the particle
void Particle::Update(float dt)
{
	if (!isAlive)
		return;
	
	//Interpolate between the initial and decay colours and transparency based on the current life of the particle
	Colour = LERP(InitialColour,DecayColour,(InitialLife/Life)-1.0f);
	Transparency = LERP(InitialTransparency, DecayTransparency, (InitialLife/Life)-1.0f);

	//If the particle does not have a target point
	if (!TargetPoint)
	{
		//Update the position of the particle
		Position += Velocity * dt + Acceleration * dt * dt * 0.5f;

		//If the particle has not hit the max speed then update it
		if (Velocity.GetLengthSqr() < MaxSpeed)
			Velocity = Velocity + Acceleration * dt;
	}
	//If the particle has a target point
	else if(TargetPoint)
	{
		//Create a temporary vector
		 Vector3<float> temp;
		 //Set the temp so that it is the acceleration magnitude in the direction of the target
		 temp = (TargetPointPosition - Position).Normalize() * AccelerationMagnitude;

		 //Update the position
		 Position += Velocity * dt + temp * dt * dt * 0.5f;

		 //If the particle has not hit max velocity, update it
		 //Needs updating
		if (Velocity.GetLengthSqr() < MaxSpeed)
			Velocity = Velocity + temp * dt;
	}

	//Update the current life
	Life -= dt;
	
	//Update the scale
	Scale -= ShrinkRate * dt;

	//Check if the particle is still alive,
	//kill it if it has run out of time or has shrunken to 0
	if (Life < 0 || Scale <= 0)
		isAlive = false;
}

void Particle::Reset()
{
}

Particle Particle::operator+(const Particle &particle) const
{
	Particle temp;

	temp.Frame = this->Frame;

	temp.InitialColour = this->InitialColour + particle.InitialColour;
	temp.DecayColour = this->DecayColour + particle.DecayColour;

	temp.InitialTransparency = this->InitialTransparency + particle.InitialTransparency;
	temp.DecayTransparency = this->DecayTransparency + particle.DecayTransparency;

	temp.Position = this->Position + particle.Position;
	temp.Velocity = this->Velocity + particle.Velocity;
	temp.Acceleration = this->Acceleration + particle.Acceleration;
	temp.Force = this->Force + particle.Force;

	temp.InitialLife = this->InitialLife + particle.InitialLife;
	temp.Mass = this->Mass + particle.Mass;
	temp.MaxSpeed = this->MaxSpeed + particle.MaxSpeed;
	temp.Scale = this->Scale + particle.Scale;
	temp.ShrinkRate = this->ShrinkRate + particle.ShrinkRate;

	temp.TargetPointPosition = this->TargetPointPosition + particle.TargetPointPosition;
	temp.AccelerationMagnitude = this->AccelerationMagnitude + particle.AccelerationMagnitude;

	if (this->Movement == particle.Movement)
		temp.Movement = this->Movement;

	if (this->TargetPoint == particle.TargetPoint)
		temp.TargetPoint = this->TargetPoint;

	temp.tex = this->tex;

	return temp;
}

Particle Particle::operator*(const float f) const
{
	Particle temp;

	temp.InitialColour = this->InitialColour * f;
	temp.DecayColour = this->DecayColour * f;

	temp.InitialTransparency = this->InitialTransparency * f;
	temp.DecayTransparency = this->DecayTransparency * f;

	temp.Position = this->Position * f;
	temp.Velocity = this->Velocity * f;
	temp.Acceleration = this->Acceleration * f;
	temp.Force = this->Force * f;

	temp.InitialLife = this->InitialLife * f;
	temp.Mass = this->Mass * f;
	temp.MaxSpeed = this->MaxSpeed * f;
	temp.Scale = this->Scale * f;
	temp.ShrinkRate = this->ShrinkRate * f;

	temp.TargetPointPosition = this->TargetPointPosition * f;
	temp.AccelerationMagnitude = this->AccelerationMagnitude * f;

	temp.Movement = this->Movement;

	temp.TargetPoint = this->TargetPoint;

	temp.tex = this->tex;

	return temp;
}