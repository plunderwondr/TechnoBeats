#ifndef _ANIMATION_MATH_H
#define _ANIMATION_MATH_H

#include "Vector.h"

// LINEAR INTERPOLATION ALGORITHMS

//// Usage 1: 1D number
//inline float LERP(const float p0, const float p1, const float t)
//{
//	////Step 1: Calculate the range or the difference between endpoints
//	//float span = p1 - p0;
//
//	////Where do we lie within the range?
//	////Step 2: Find where we are relative to the start by multiplying by t
//	//float relative = span * t; //(p1 - p0) * t
//
//	////Where do we lie between our actual endpoints?
//	////Step 3: Add p0 to put us back within our original endpoints
//	//float result = relative + p0;
//
//	////Condensed form #1
//	float result = (p1 - p0) * t + p0;
//
//	////Condensed form #2
//	//float result = (1.0f - t) * p0 + (t) * p1;
//
//	return result;
//}
//
////Usage 2: 2D
//inline Vector2<float> LERP (const Vector2<float> p0, const Vector2<float> p1, const float t)
//{
//	Vector2<float> result;
//	// 2 ways to do this

	//1)
	//result.x = LERP(p0.x, p1.x, t);
	//result.y = LERP(p0.y, p1.y, t);

	//2)
//	result = (p1 - p0) * t + p0;
//	//result = (1.0f - t) * p0 + (t) * p1;
//
//	return result;
//}
//
////Usage 3: 3D
//inline Vector3<float> LERP (const Vector3<float> p0, const Vector3<float> p1, const float t)
//{
//	Vector3<float> result;
//	// 2 ways to do this
//
//	//1)
//	//result.x = LERP(p0.x, p1.x, t);
//	//result.y = LERP(p0.y, p1.y, t);
//	//result.z = LERP(p0.z, p1.z, t);
//
//	//2)
//	result = (p1 - p0) * t + p0;
//	//result = (1.0f - t) * p0 + (t) * p1;
//
//	return result;
//}

// Usage 4: GENERIC
template <typename lerpClass>
inline lerpClass LERP(const lerpClass p0, const lerpClass p1, const float t)
{
	//return ( (1.0f - t) * p0 + (t) * p1 );
	return ( (p1 - p0) * t + p0 );
}

template <typename lerpClass>
inline lerpClass BLEND(const lerpClass p0, const lerpClass p1, const float t)
{
	return (p0 * (1.0f - t) + p1 * (t));
}

template <typename catmullromClass>
inline catmullromClass CatmullRom(const catmullromClass preStart, //p_i_1
								  const catmullromClass start,    //p_i
								  const catmullromClass end,      //p_i1
								  const catmullromClass postEnd,  //p_i2
								  const float t)
{
	catmullromClass result = ((start * 2)
							+ (preStart * -1 + end) * t
							+ (preStart*2 - start * 5 + end * 4 - postEnd) * (t*t)
							+ (preStart * -1 + start * 3 - end * 3 + postEnd) * (t*t*t))
							* 0.5f;

	return result;
}
#endif