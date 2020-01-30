#include "Animation.h"

//Default constructor
Animation::Animation(void)
{
	//Set all values to 0
	Loop = false;
	running = false;

	runTime = 0;
	segmentTime = 0;
	currentTime = 0;

	currentFrame = 0;
	nextFrame = 0;
}


Animation::~Animation(void)
{
}

//Update the current model
void Animation::Update(float dt)
{
	//If the animation is running
	if (running)
	{
		currentTime+=dt;					//Increment the animation based on the change in time

		if (currentTime >= segmentTime)		//If the currentTime is greater than the segment time
		{
			currentTime-=segmentTime;		//Reset the currentTime
			Next();							//Check which keyframes to go to
		}

		//Interpolate between the two keyframes to get the current frame
		*current = BLEND(keyframes[currentFrame], keyframes[nextFrame],currentTime);
	}
}