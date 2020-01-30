#include "CatmullPath.h"


CatmullPath::CatmullPath(void)
{
	Running = false;
}


CatmullPath::~CatmullPath(void)
{
}

void CatmullPath::Update(float dt)
{
	if (Running)
	{
		currentTime+=dt;

		if(currentTime > SegmentTime)
		{
			NextWaypoint();
		}

		current = CatmullRom(Waypoints[prevIndex], Waypoints[currentIndex],
							 Waypoints[nextIndex], Waypoints[followingIndex],
							 (currentTime/SegmentTime));
	}
}

void CatmullPath::NextWaypoint()
{
	
	currentTime -= SegmentTime;
	prevIndex = currentIndex;
	currentIndex = nextIndex;
	
	if (currentIndex == Waypoints.size()-1)
	{
		Running = false;
	}

	if (currentIndex == Waypoints.size()-2)
	{
		nextIndex = followingIndex;
	}
	else if (currentIndex < Waypoints.size()-2)
	{
		nextIndex = followingIndex;
		followingIndex++;
	}
}