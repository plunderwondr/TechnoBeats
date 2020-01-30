#ifndef COORDFRAME_H
#define COORDFRAME_H

#pragma once

#include "Vector.h"

class coordFrame
{
public:
	coordFrame(void)
	{
		Dir.setPosition(0.0f,0.0f,1.0f);

		Right.setPosition(1.0f,0.0f,0.0f);

		Up.setPosition(0.0f,1.0f,0.0f);
	}

	~coordFrame(void)
	{
	}

	inline void setDir(Vector3<> _Dir)
	{
		Dir = _Dir;
	}

	inline void setRight(Vector3<> _Right)
	{
		Right = _Right;
	}

	inline void calcUp()
	{
		Up = Dir.Cross(Right);
	}

	inline void recalc()
	{
		Right = Dir.Cross(Vector3<>(0.0,1.0f,0.0));
		Up = Dir.Cross(Right);
	}

	Vector3<float> Dir;
	Vector3<float> Right;
	Vector3<float> Up;
};

#endif COORDFRAME_H