#include "Camera.h"


Camera::Camera(void)
{
	Position.setPosition(0.0,0.0,0.0);
	cameraFrame.setDir(Vector3<float>(1.0,0.0,0.0));
	cameraFrame.setRight(Vector3<float>(1.0,0.0,1.0));
	cameraFrame.recalc();
}


Camera::~Camera(void)
{
}
