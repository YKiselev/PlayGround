#include "Matrix4D.h"

namespace Math
{

	Matrix4D::Matrix4D() : c1r1{ 1 }, c1r2{ 0 }, c1r3{ 0 }, c1r4{ 0 },
		c2r1{ 0 }, c2r2{ 1 }, c2r3{ 0 }, c2r4{ 0 },
		c3r1{ 0 }, c3r2{ 0 }, c3r3{ 1 }, c3r4{ 0 },
		c4r1{ 0 }, c4r2{ 0 }, c4r3{ 0 }, c4r4{ 1 }
	{
	}

	Matrix4D::Matrix4D(const float src[16]) : c1r1{ src[0] }, c1r2{ src[1] }, c1r3{ src[2] }, c1r4{ src[3] },
		c2r1{ src[4] }, c2r2{ src[5] }, c2r3{ src[6] }, c2r4{ src[7] },
		c3r1{ src[8] }, c3r2{ src[9] }, c3r3{ src[10] }, c3r4{ src[11] },
		c4r1{ src[12] }, c4r2{ src[13] }, c4r3{ src[14] }, c4r4{ src[15] }
	{

	}

	void Matrix4D::orthographic(float left, float right, float top, float bottom, float, float)
	{
	}

	void Matrix4D::perspective(float left, float right, float top, float bottom, float, float)
	{
	}

	void Matrix4D::perspective(float fow, float ratio, float, float)
	{
	}


	Matrix4D& Matrix4D::rotate(float ax, float ay, float az)
	{
		return (*this);
	}

	Matrix4D& Matrix4D::inverse()
	{
		return (*this);
	}

	double Matrix4D::determinant() const
	{
		return 0.0;
	}

}