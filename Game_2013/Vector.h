/*****************************\
*Cameron Nicoll's Vector Class*
*Made with lots of love!      *
\*****************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#pragma once

//2D Vectors
template<class var = float>
class Vector2
{
public:
	//Default Constructor
	inline Vector2()
	{
		x = y = 0;			//Initialize with 0
	}

	//Constructor with starting values
	inline Vector2(var _x, var _y)
	{
		//Assign x and y values
		x = _x;			
		y = _y;
	}

	//Set the values of the vector
	inline void setPosition(var _x, var _y)
	{
		//Assign values to x and y
		x = _x;
		y = _y;
	}

	//Get the dot product of this vector and another
	inline var Vector2<var>::dotProduct(Vector2 _vec)
	{
		//Return scalar value
		return ((x * _vec.x) + (y * _vec.y));
	}

	//Overload addition and subtraction operators
	inline Vector2<var> operator+ (const Vector2 &_vec) const
	{
		Vector2<var> result;
		result.x = x + _vec.x;
		result.y = y + _vec.y;
		return result;
	}

	inline Vector2<var>& operator+= (const Vector2 &_vec)
	{
		this->x = x + _vec.x;
		this->y = y + _vec.y;
		return *this;
	}

	inline Vector2<var> operator- (const Vector2 &_vec) const
	{
		Vector2<var> result;
		result.x = x - _vec.x;
		result.y = y - _vec.y;
		return result;
	}

	inline Vector2<var>& operator-= (const Vector2 &_vec)
	{
		this->x = x - _vec.x;
		this->y = y - _vec.y;
		return *this;
	}
	
	inline Vector2<var> operator* (const float f) const
	{
		return Vector2<var>(x * f, y * f);
	}
	
	inline Vector2<var> operator/ (const float f) const
	{
		return Vector2<var>(x / f, y / f);
	}

	//Overload comparison operators
	bool operator== (const Vector2 &_vec) const
	{
		if (x == _vec.x && y == _vec.y)
			return true;
		else
			return false;
	}

	bool operator!= (const Vector2 &_vec) const
	{
		if (x == _vec.x && y == _vec.y)
			return false;
		else
			return true;
	}

	//Variables
	var x, y;

};

//3D Vectors
template<class var = float>
class Vector3
{
public:
	//Default constructor
	inline Vector3()
	{
		x = y = z = 0;		//Initialize to 0
	}

	//Overloaded constructor
	inline Vector3(var _x, var _y, var _z)
	{
		//Set based on x, y, z values
		x = _x;
		y = _y;
		z = _z;
	}

	//setPosition
	inline void setPosition(var _x, var _y, var _z)
	{
		//Set based on x, y, z values
		x = _x;
		y = _y;
		z = _z;
	}

	//setPosition
	inline void setPosition(Vector3<var> _vec)
	{
		//Set based on x, y, z values
		x = _vec.x;
		y = _vec.y;
		z = _vec.z;
	}

	//getVector
	inline Vector3<var> getVector() const
	{
		return Vector3<var>(x,y,z);		//Return the vector
	}
	//////////////////Begin Operators//////////////////////
	
	//All overloaded operators that use another Vector3 as the parameter and return a vector3
	inline Vector3<var> operator+ (const Vector3 &_vec) const
	{
		Vector3<var> result;
		result.x = x + _vec.x;
		result.y = y + _vec.y;
		result.z = z + _vec.z;
		return result;
	}
	
	inline Vector3<var> operator- (const Vector3 &_vec) const
	{
		Vector3<var> result;
		result.x = x - _vec.x;
		result.y = y - _vec.y;
		result.z = z - _vec.z;
		return result;
	}
	
	inline Vector3<var> operator* (const Vector3 &_vec) const
	{
		return Vector3<var>(x * _vec.x, y * _vec.y, z * _vec.z);
	}
	
	inline Vector3<var> operator/ (const Vector3 &_vec) const
	{
		return Vector3<var>(x / _vec.x, y / _vec.y, z / _vec.z);
	}

	//All overloaded operators that use another Vector3 as the parameter but update the values of the current vector
	inline Vector3<var>& operator+= (const Vector3 &_vec)
	{
		this->x += _vec.x;
		this->y += _vec.y;
		this->z += _vec.z;
		return *this;
	}

	inline Vector3<var>& operator-= (const Vector3 &_vec)
	{
		this->x -= _vec.x;
		this->y -= _vec.y;
		this->z -= _vec.z;
		return *this;
	}

	inline Vector3<var>& operator*= (const Vector3 &_vec)
	{
		this->x *= _vec.x;
		this->y *= _vec.y;
		this->z *= _vec.z;
		return *this;
	}

	inline Vector3<var>& operator/= (const Vector3 &_vec)
	{
		this->x /= _vec.x;
		this->y /= _vec.y;
		this->z /= _vec.z;
		return *this;
	}

	//Overloaded = operator, assign another vector to this one
	inline Vector3<var>& operator= (const Vector3 &_vec)
	{
		this->x = _vec.x;
		this->y = _vec.y;
		this->z = _vec.z;
		return *this;
	}

	//Overloaded bool operators
	inline bool operator== (const Vector3 &_vec) const
	{
		if (x == _vec.x && y == _vec.y && z == _vec.z)
			return true;
		else
			return false;
	}

	inline bool operator!= (const Vector3 &_vec) const
	{
		if (x == _vec.x && y == _vec.y && z == _vec.z)
			return false;
		else
			return true;
	}
	
	//Overloaded operators that use scalar values
	inline Vector3<var> operator* (const float f) const
	{
		return Vector3<var>(x * f, y * f, z * f);
	}
	
	inline Vector3<var> operator/ (const float f) const
	{
		return Vector3<var>(x / f, y / f, z / f);
	}

	//////////////////End Operators//////////////////////
	
	/////////////Begin Vector Operations/////////////////

	//Dot product of this vector and another
	inline var Vector3<var>::Dot(const Vector3 _vec) const
	{
		return ((x * _vec.x) + (y * _vec.y) + (z * _vec.z));
	}

	//Negate the vector
	inline void Vector3<var>::Negate() const
	{
		x = -x;
		y = -y;
		z = -z;
	}

	//Return the squared length of the vector
	inline float Vector3<var>::GetLengthSqr() const
	{
		return (x * x + y * y + z * z);
	}

	//Return the length of the vector
	inline float Vector3<var>::GetLength() const
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	//Normalize the vector
	inline Vector3<var> Vector3<var>::Normalize() const
	{
		//Get the length
		float len = GetLength();

		//If the vector length is greater than 0, it can be normalized
		if (len != 0)
			len = 1.0f/len;
		else
			len = 1.0f;

		//Return the normalized version of the vector
		return Vector3<var>(x * len, y * len, z * len);
	}

	//Cross product of this vector and another
	inline Vector3<var> Vector3<var>::Cross(const Vector3<var> _vec) const
	{
		return Vector3<var>(y * _vec.z - z * _vec.y,
				z * _vec.x - x * _vec.z,
				x * _vec.y - y * _vec.x);
	}

	//Project this vector on to another vector
	inline Vector3<var> Vector3<var>::Projection(const Vector3<var> _vec) const
	{
		return (_vec * (this->Dot(_vec) / (_vec.Dot(_vec))));
	}

	//Project this vector on to another vector and return a Scalar
	inline var Vector3<var>::ProjectionS(const Vector3<var> _vec) const
	{
		return (this->Dot(_vec) / _vec.GetLength());
	}
	/////////////End Vector Operations/////////////////
	
	//Variables
	var x, y, z;

};

//UV Vector...Basically a 2D with less functionality
class UV_Vector
{
public:
	//Default constructor
	inline UV_Vector()
	{
		u = v = 0;	//Initialize values at 0
	}

	//Overloaded constructor
	inline UV_Vector(float _u, float _v)
	{
		//Initialize with input values
		u = _u;
		v = _v;
	}

	//Set the values of u and v
	inline void setValues(float _u, float _v)
	{
		u = _u;
		v = _v;
	}

	inline UV_Vector operator+ (const UV_Vector &_vec) const
	{
		UV_Vector result;
		result.u = u + _vec.u;
		result.v = v + _vec.v;
		return result;
	}

	//Variables
	float u, v;
};

#endif