#include "EventManager.h"
#include "MessageRelay.h"

#include <iostream>
EventManager *EventManager::instance;

//Sort the entities so that they are in order by index
bool SortByEnemyTime(EnemySpawnEvent EnemySpawn1, EnemySpawnEvent EnemySpawn2)
{
	return (EnemySpawn1.TriggerTime > EnemySpawn2.TriggerTime);
}

bool SortByTime(Event Event1, Event Event2)
{
	return (Event1.TriggerTime > Event2.TriggerTime);
}

EventManager::EventManager(void)
{
}


EventManager::~EventManager(void)
{
}

void EventManager::LoadEvents()
{
	GameTime = 0.0f;

	int fileEnd = 1;	//fileEnd, used for checking if we have reached the end of the file. Initialized to 1 to start the loop.
	char line[32];		//Char array, used for assigning values from the file stream
	FILE* events;	//FILE pointer, the stream for the obj file is assigned to this value so it can be read
	events = fopen("EventList.txt", "rt");		//Open the stream and assign it to our FILE variable, uses the file sent in. "rt" makes it read-only text
	
	Vector3<float> SpawnPosition;
	Vector3<float> SpawnOrientation;
	int EnemyType;
	float Trigger;

	//Loop while the program is not at the end of the file
	while (fileEnd != EOF)							
	{
		fileEnd = fscanf(events, "%s", line);	//Scan the file stream for a string, assign the first string encountered to the line variable (array of characters)
	
		//Check if the string is a v (vertex), vt (texture vertex), vn (normal vector)
		//or f (face).

		//If the string is v...
		if (strcmp(line, "EnemySpawn:" ) == 0)
		{
			fscanf(events, "%f,%f,%f/%f,%f,%f/%i/%f", &SpawnPosition.x, &SpawnPosition.y, &SpawnPosition.z,
													&SpawnOrientation.x, &SpawnOrientation.y, &SpawnOrientation.z,
													&EnemyType, &Trigger);	//Search the stream for 3 float values separated by spaces and assign them to the temporary Vertex
			AddEnemySpawn(SpawnPosition, SpawnOrientation, EnemyType, Trigger);
		}
		else if (strcmp(line, "End:" ) == 0)
		{
			fscanf(events, "%f", &Trigger);	//Search the stream for 3 float values separated by spaces and assign them to the temporary Vertex
			AddEvent(1,Trigger);
		}
	}
	
	fclose(events);						//Close the stream...VERY IMPORTANT
}

void EventManager::Update(float dt)
{
	unsigned int vectorSize;
	GameTime += dt;

	std::sort(EnemySpawnEventList.begin(), EnemySpawnEventList.end(), SortByEnemyTime);
	std::sort(EventList.begin(), EventList.end(), SortByTime);
	
	vectorSize = EnemySpawnEventList.size();

	if (vectorSize > 0)
	{
		while (EnemySpawnEventList[vectorSize-1].TriggerTime <= GameTime)
		{

			if (EnemySpawnEventList[vectorSize-1].EnemyType < EnemyList.size())
			{
				EnemyList[EnemySpawnEventList[vectorSize-1].EnemyType].NewEnemy(EnemySpawnEventList[vectorSize-1].Position,EnemySpawnEventList[vectorSize-1].Orientation);
				
				EnemySpawnEventList.pop_back();
				std::cout << "enemey";
			}
			
			vectorSize = EnemySpawnEventList.size();

			if (vectorSize == 0)
				break;
		}
	}
	
	vectorSize = EventList.size();

	if (vectorSize > 0)
	{
		while (EventList[vectorSize-1].TriggerTime <= GameTime)
		{
			
			if (EventList[vectorSize-1].Type == 1)
				MessageRelay::GetInstance()->ReturnToMenu();

			EventList.pop_back();

			vectorSize = EventList.size();

			if (vectorSize == 0)
				break;
		}
	}
}

void EventManager::Reset()
{
	GameTime = 0.0f;
}