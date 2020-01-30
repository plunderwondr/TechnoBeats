

#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "Vector.h"


// simple quaternion class
// used for rotations and orientations
class Quaternion
{
public: 

	// construct as IDENTITY
	Quaternion()
	{
		w = 1.0f;
		x = y = z = 0.0f;
	}


	// construct as four numbers
	Quaternion(float _w, float _x, float _y, float _z)
	{
		w = _w;
		x = _x;
		y = _y;
		z = _z;
	}


	// construct as angle-axis (angle in radians)
	// **** CHANGE THIS TO REFLECT THE MATH LIBRARY YOU ARE USING!
	Quaternion(float angleRadians, 
			   const Vector3<float> axis)
	{
		// **** IMPLEMENT THIS!
		w = cos(angleRadians/2);
		u = axis * sin(angleRadians/2);
	}


	// get components
	inline float GetW() const { return w; }
	inline float GetScalar() const { return w; }

	inline float GetX() const { return x; }
	inline float GetY() const { return y; }
	inline float GetZ() const { return z; }

	// **** CHANGE THIS TOO!
	inline Vector3<float> GetVector() const { return u; }


	// mathematical operations

	// get the CONJUGATE of this quaternion
	inline Quaternion GetConjugate() const
	{
		return Quaternion(w, -x, -y, -z);
	}


	// you can add, subtract and scale quaternions, too!
	inline Quaternion operator+(const Quaternion q) const
	{
		return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
	}
	inline Quaternion operator-(const Quaternion q) const
	{
		return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
	}
	inline Quaternion operator*(const float scalar) const
	{
		return Quaternion(w*scalar, x*scalar, y*scalar, z*scalar);
	}

	inline float dot(const Quaternion q) const
	{
		return (w*q.w + x*q.x + y*q.y + z*q.z);
	}

	// **** NEED TO FILL THESE OUT!!!!

	// **** multiply with another quaternion
	inline Quaternion operator*(const Quaternion q2) const
	{
		const Quaternion q1 = *this;
		
		// **** take note of the formula we use: 
		//	q1 * q2: implies that the argument above is on the right
		// **** remember that multiplication is not commutative, so 
		//	make sure you are doing this right!
		Quaternion temp; //Get rid of once you have proper Vector library
		temp.w = q1.w*q2.w - (q1.u.Dot(q2.u));

		temp.u = q2.u * q1.w + q1.u * q2.w + (q1.u.Cross(q2.u));

		return temp;
	}


	// **** function to make this an angle-axis quaternion
	//	used for rotations
	inline Quaternion &MakeAngleAxis(float angleRadians, 
									 const Vector3<float> axis)
	{
		// **** IMPLEMENT
		w = cos(angleRadians/2);
		u = axis * sin(angleRadians/2);
		return *this;
	}


	// **** use this quaternion to rotate a vector
	//	again, change the argument to reflect the math library
	inline Vector3<float> RotateVector(const Vector3<float> vec) const
	{

		return Vector3<float>(vec + ((u) * 2).Cross(u.Cross(vec) + (vec*w)));
	}


private: 

	// scalar component
	float w;

	// vector component
	// **** PROGRAMMING CONCEPT: UNION!
	// **** TAKE NOTES!
	union
	{
		struct {
			float x, y, z;
		};
		struct {
			Vector3<float> u;
		};
	};

};




// **** SLERP
// implement this!
inline Quaternion SLERP(const Quaternion q0, 
						const Quaternion q1, 
						const float t)
{
	float angle;
	Quaternion temp = q0;
	Quaternion temp2 = q1;

	angle = acos( (temp.GetVector()).Normalize().Dot((temp2.GetVector()).Normalize()) );

	// **** implement slerp
	return Quaternion(q0 * (sin( (1.0f - t) * angle) / sin(angle)) + q1 * (sin(t * angle)/sin(angle)));
}

inline Vector3<float> SLERP(const Vector3<float> q0, 
						const Vector3<float> q1, 
						const float t)
{
	float angle;
	Vector3<float> temp = q0;
	Vector3<float> temp2 = q1;
	Vector3<float> result;

	if (temp == temp2)
		result = temp;
	else
	{
		temp = temp.getVector().Normalize();
		temp2 = temp2.getVector().Normalize();

		angle = acos( temp.Dot(temp2) );

		// **** implement slerp
		result =  Vector3<float>(q0 * (sin( (1.0f - t) * angle) / sin(angle)) + q1 * (sin(t * angle)/sin(angle)));
	}

	return result;
}



#endif	// _QUATERNION_H