#pragma once
#include "Quaternion.h"
#include "Vector.h"
#include <vector>

class OrientationPath
{
public:
	OrientationPath(void);
	~OrientationPath(void);

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
		currentIndex = 0;
		nextIndex = 1;
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

	unsigned int currentIndex;
	unsigned int nextIndex;

	std::vector<Vector3<float>> Waypoints;
	Vector3<float> current;

	bool Running;
	float currentTime;
	float SegmentTime;
	float RunTime;
};

