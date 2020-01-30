#pragma once
#include "AnimationMath.h"
#include "Vector.h"
#include <vector>

class CatmullPath
{
public:
	CatmullPath(void);
	~CatmullPath(void);

	void AddWaypoint(Vector3<float> point)
	{
		Waypoints.push_back(point);
	}

	void RemoveLastWaypoint()
	{
		Waypoints.pop_back();
	}

	void ClearWaypoints()
	{
		Waypoints.clear();
	}

	inline void Start()
	{
		Running = true;
		prevIndex = 0;
		currentIndex = 0;
		nextIndex = 1;
		followingIndex = 2;
	}

	inline void Stop()
	{
		Running = false;
	}

	inline void SetTime(float time)
	{
		RunTime = time;
		SegmentTime = RunTime/(Waypoints.size()-1);
	}

	void Update(float dt);

	inline Vector3<float> GetCurrentPoint() const
	{
		return current;
	}

	inline bool GetRunning() const
	{
		return Running;
	}

private:
	void NextWaypoint();

	unsigned int prevIndex;
	unsigned int currentIndex;
	unsigned int nextIndex;
	unsigned int followingIndex;

	std::vector<Vector3<float>> Waypoints;
	Vector3<float> current;

	bool Running;
	float currentTime;
	float SegmentTime;
	float RunTime;
};

