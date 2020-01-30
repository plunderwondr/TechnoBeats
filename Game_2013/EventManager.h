#pragma once

#include "MessageRelay.h"
#include "Enemy.h"
#include "Vector.h"

struct Event
{
	unsigned int Type;

	float TriggerTime;
};

struct EnemySpawnEvent
{
	Vector3<float> Position;
	Vector3<float> Orientation;
	unsigned int EnemyType;

	float TriggerTime;
};

class EventManager
{
public:
	static EventManager* GetInstance()
	{
		if (!instance)
			instance = new EventManager();

		return instance;
	}

	//Terminate the instance
	void Terminate()
	{
		//If the instance exists, delete it
		if(instance)
			instance->~EventManager();
	}

	void AddEnemy(Enemy EnemyEntity)
	{
		EnemyList.push_back(EnemyEntity);
	}

	void LoadEvents();

	void AddEvent(unsigned int EventType, float Trigger)
	{
		Event temp;
		temp.Type = EventType;
		temp.TriggerTime = Trigger;

		EventList.push_back(temp);
	}

	void AddEnemySpawn(Vector3<float> spawnPosition, Vector3<float> spawnOrientation, unsigned int EnemyNumber, float time)
	{
		EnemySpawnEvent temp;
		temp.Position = spawnPosition;
		temp.Orientation = spawnOrientation;
		temp.EnemyType = EnemyNumber;
		temp.TriggerTime = time;

		EnemySpawnEventList.push_back(temp);
	}

	void Update(float dt);

	void Reset();
private:
	EventManager(void);
	~EventManager(void);

	float GameTime;

	static EventManager* instance;

	std::vector<Enemy> EnemyList;
	std::vector<EnemySpawnEvent> EnemySpawnEventList;
	std::vector<Event> EventList;
};


