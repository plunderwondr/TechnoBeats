#pragma once
#include "Vector.h"
#include "coordFrame.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

	Vector3<float> Position;
	coordFrame cameraFrame;
	Vector3<float> Target;
};

