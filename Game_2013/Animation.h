//Work in progress
//To add:
//Ping-ponging


#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include "Model.h"
#include "AnimationMath.h"
#include <vector>

class Animation
{
public:
	//Default constructor
	Animation(void);
	~Animation(void);

	//Set the loop
	void setLoop(bool loop)
	{
		Loop = loop;
	}

	//Return the current state of the Loop
	bool getLoop()
	{
		return Loop;
	}

	//Start the animation
	void start()
	{
		//Set to the first and second keyframes
		currentFrame = 0;
		nextFrame = 1;
		//Set runnning to true
		running = true;
	}

	//Stop the animation
	void stop()
	{
		//Set to the first and second keyframes
		currentFrame = 0;
		nextFrame = 1;

		//Set currentTime to 0
		currentTime = 0;

		//Set running to false
		running = false;
	}

	//Set the run time of the animation
	void setTime(float t)
	{
		//Set the full runtime of the animation
		runTime = t;

		//Set the segment time based on the number of keyframes
		segmentTime = runTime/keyframes.size();
	}

	//Get the full run time
	float getTime()
	{
		return runTime;
	}

	//Get the current model
	Model* getCurrent()
	{
		return current;
	}

	//Add a keyframe
	void addFrame(Model model)
	{
		keyframes.push_back(model);
	}

	//Delete the last keyframe
	void deleteFrame()
	{
		keyframes.pop_back();
	}

	//Clear all the frames
	void clearFrames()
	{
		keyframes.clear();
	}
	
	//Transition to the next frame or stop if it's at the end
	void Next()
	{
		//If the animation is not looping and it's at the end, stop
		if (!Loop && nextFrame == keyframes.size()-1)
			stop();
		//If the animation is set to loop and it's at the end
		else if (Loop && nextFrame == keyframes.size()-1)
		{
			currentFrame = nextFrame;	//Set the nextFrame to be the currentFrame
			nextFrame = 0;				//Set the nextFrame to the first
		}
		//If the animation is not at the end
		else if (nextFrame != keyframes.size()-1)
		{
			currentFrame = nextFrame;	//Set the nextFrame to be the currentFrame
			nextFrame++;				//Increment the nextFrame
		}
	}

	//Update the current model
	void Update(float dt);

	std::vector<Model> keyframes;	//Dynamic array of the keyframes
	Model *current;					//Pointer to the current model

	unsigned int currentFrame;		//Keep track of current keyframe
	unsigned int nextFrame;			//Keep track of next keyframe

	bool Loop;						//Keep track of whether the animation is looping
	bool running;					//Keep track of whether the animation is running

	float runTime;					//The full run time
	float segmentTime;				//The time between each keyframe
	float currentTime;				//The current time of the animation
};

#endif