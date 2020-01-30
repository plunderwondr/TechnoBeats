#include "MessageRelay.h"
#include "ParticleManager.h"

MessageRelay *MessageRelay::instance;

MessageRelay::MessageRelay(void)
{
	End = false;
}


MessageRelay::~MessageRelay(void)
{
}

void MessageRelay::Explode(Vector3<float> position)
{
	ParticleSystem *test = new ParticleSystem();
	test->SetPosition(Vector3<float>(position));
	test->SetVelocity(Vector3<>(0.0, 0.0, 0.0));
	test->SetSpreadDeviation(Vector3<>(-1.5f,0.0f,-1.5f),Vector3<>(1.5f,0.0f,1.5f));
	test->SetSpawnDeviation(Vector3<>(),Vector3<>());
	test->SetLifeDeviation(0.5f);
	test->SetScaleDeviation(0.3f);
	test->SetExplosion(Explosion);
	test->SetRunType(0);
	test->SetRunTimes(10);
	
	coordFrame tempFrame;
	tempFrame.setDir(Vector3<>(0.0,1.0,0.0));
	tempFrame.setRight(Vector3<>(1.0,0.0,0.0));
	tempFrame.calcUp();
	
	//Particle
	Particle temp;
	temp.SetCoordFrame(&tempFrame);
	temp.SetInitialColour(Vector3<>(1.0,0.3,1.0),1.0f);
	temp.SetDecayColour(Vector3<>(0.0,1.0,1.0),0.6f);
	temp.SetLife(0.5f);
	temp.SetMaxSpeed(1000);
	temp.SetMass(1.0f);
	temp.SetScale(1.0f);
	temp.SetShrinkRate(0.001f);
	temp.ApplyForce(Vector3<>(0.0,0.0f,0.1f));
	temp.LoadFile("Particle/test.png");
	
	test->Initialize(200,200);
}