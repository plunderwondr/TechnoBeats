#pragma once

#include "Vector.h"

//A really bad pseudo-messenger system. A better created one will be created and implemented next term

class MessageRelay
{
public:
	static MessageRelay* GetInstance()
	{
		if (!instance)
			instance = new MessageRelay();

		return instance;
	}

	//Terminate the instance
	void Terminate()
	{
		//If the instance exists, delete it
		if(instance)
			instance->~MessageRelay();
	}

	int PlayerMessage()
	{
		return playerAbility;
	}

	void ActivateAbility(unsigned int ability)
	{
		playerAbility = ability;
	}

	void ReturnToMenu()
	{
		End = true;
	}

	bool EndMessage()
	{
		return End;
	}
	
	void ResetEnd()
	{
		End = false;
	}

	void ResetPlayer()
	{
		playerAbility = -1;
	}

	void Explode(Vector3<float> position);

	int playerAbility;

private:
	MessageRelay(void);
	~MessageRelay(void);

	bool End;

	static MessageRelay *instance;
};