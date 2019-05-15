#pragma once

#include <cmath>

namespace Math
{
	struct Vector3D
	{
		float x, y, z;

		Vector3D() : x{ 0 }, y{ 0 }, z{ 0 } {};
		Vector3D(float x, float y, float z) : x{ x }, y{ y }, z{ z }{};

		Vector3D normalized() const;
		float length() const;
		float lengthSquared() const;
		float dotProduct(const Vector3D& other) const;
		Vector3D crossProduct(const Vector3D& other) const;

		bool operator == (const Vector3D& other) const;
		bool operator != (const Vector3D& other) const;
		Vector3D operator * (float scale) const;
		Vector3D operator / (float scale) const;
		Vector3D operator + (const Vector3D& other) const;
		Vector3D operator - (const Vector3D& other) const;
		Vector3D operator * (const Vector3D& other) const;
		Vector3D operator / (const Vector3D& other) const;
		Vector3D operator - () const;
	};


	inline float Vector3D::dotProduct(const Vector3D& b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

	inline Vector3D Vector3D::crossProduct(const Vector3D& other) const
	{
		return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}

	inline float Vector3D::lengthSquared() const
	{
		return dotProduct(*this);
	}

	inline float Vector3D::length() const
	{
		return std::sqrt(lengthSquared());
	}

	inline Vector3D Vector3D::normalized() const
	{
		const float l = length();
		float ool = 1.0;
		if (l != 0) {
			ool = 1.0f / l;
		}
		return { x * ool, y * ool, z * ool };
	}

	inline bool Vector3D::operator == (const Vector3D& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	inline bool Vector3D::operator != (const Vector3D& other) const
	{
		return !(*this == other);
	}

	inline Vector3D Vector3D::operator * (float scale) const
	{
		return { x * scale, y * scale, z * scale };
	}

	inline Vector3D Vector3D::operator / (float scale) const
	{
		return (*this)* (1.0f / scale);
	}

	inline Vector3D Vector3D::operator + (const Vector3D & other) const
	{
		return { x + other.x, y + other.y,z + other.z };
	}

	inline Vector3D Vector3D::operator - (const Vector3D & other) const
	{
		return { x - other.x,y - other.y,z - other.z };
	}

	inline Vector3D Vector3D::operator * (const Vector3D & other) const
	{
		return { x * other.x,y * other.y,z * other.z };
	}

	inline Vector3D Vector3D::operator / (const Vector3D & other) const
	{
		return { x / other.x,y / other.y, z / other.z };
	}

	inline Vector3D Vector3D::operator - () const
	{
		return { -x, -y, -z };
	}
}