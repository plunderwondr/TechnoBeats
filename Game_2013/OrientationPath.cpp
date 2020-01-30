#include "OrientationPath.h"


OrientationPath::OrientationPath(void)
{
}


OrientationPath::~OrientationPath(void)
{
}

void OrientationPath::Update(float dt)
{
	if (Running)
	{
		currentTime+=dt;

		if(currentTime > SegmentTime)
		{
			NextWaypoint();
		}

		current = SLERP(Waypoints[currentIndex],
						Waypoints[nextIndex],
						(currentTime/SegmentTime));
	}
}

void OrientationPath::NextWaypoint()
{
	currentTime -= SegmentTime;
	currentIndex = nextIndex;

	if (currentIndex == Waypoints.size()-1)
	{
		Running = false;
	}

	if (currentIndex < Waypoints.size()-1)
	{
		nextIndex++;
	}
}
