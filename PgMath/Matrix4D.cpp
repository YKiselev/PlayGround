#include <cmath>
#include "Matrix4D.h"


namespace Math
{

	Matrix4D::Matrix4D(const float src[16]) : c1r1{ src[0] }, c1r2{ src[1] }, c1r3{ src[2] }, c1r4{ src[3] },
		c2r1{ src[4] }, c2r2{ src[5] }, c2r3{ src[6] }, c2r4{ src[7] },
		c3r1{ src[8] }, c3r2{ src[9] }, c3r3{ src[10] }, c3r4{ src[11] },
		c4r1{ src[12] }, c4r2{ src[13] }, c4r3{ src[14] }, c4r4{ src[15] }
	{
	}

	Matrix4D::Matrix4D(
		float c1r1, float c1r2, float c1r3, float c1r4,
		float c2r1, float c2r2, float c2r3, float c2r4,
		float c3r1, float c3r2, float c3r3, float c3r4,
		float c4r1, float c4r2, float c4r3, float c4r4
	) : c1r1(c1r1), c1r2(c1r2), c1r3(c1r3), c1r4(c1r4),
		c2r1(c2r1), c2r2(c2r2), c2r3(c2r3), c2r4(c2r4),
		c3r1(c3r1), c3r2(c3r2), c3r3(c3r3), c3r4(c3r4),
		c4r1(c4r1), c4r2(c4r2), c4r3(c4r3), c4r4(c4r4)
	{
	}

	Matrix4D Matrix4D::orthographic(float left, float right, float top, float bottom, float near, float far)
	{
		return Matrix4D(
			2 / (right - left), 0, 0, 0,
			0, 2 / (top - bottom), 0, 0,
			0, 0, -2 / (far - near), 0,
			-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1
		);
	}

	Matrix4D Matrix4D::perspective(float left, float right, float top, float bottom, float near, float far)
	{
		return Matrix4D(
			2 * near / (right - left), 0, 0, 0,
			0, 2 * near / (top - bottom), 0, 0,
			(right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1,
			0, 0, -2 * far * near / (far - near), 0
		);
	}

	Matrix4D Matrix4D::perspective(float fow, float ratio, float near, float far)
	{
		const float w = near * std::tan(0.5f * fow);
		const float h = w / ratio;
		return perspective(-w, w, h, -h, near, far);
	}

	Matrix4D Matrix4D::lookAt(const Vector3D & target, const Vector3D & eye, const Vector3D & up)
	{
		const Vector3D zaxis = (eye - target).normalized();
		const Vector3D xaxis = up.crossProduct(zaxis).normalized();
		const Vector3D yaxis = zaxis.crossProduct(xaxis);
		const Matrix4D m = Matrix4D(
			xaxis.x, xaxis.y, xaxis.z, 0,
			yaxis.x, yaxis.y, yaxis.z, 0,
			zaxis.x, zaxis.y, zaxis.z, 0,
			0, 0, 0, 1
		);
		return (~Matrix4D()) - eye;
	}

	Matrix4D Matrix4D::rotate(float ax, float ay, float az) const
	{
		return Matrix4D();
	}

	Matrix4D Matrix4D::inverse() const
	{
		return Matrix4D();
	}

	double Matrix4D::determinant() const
	{
		return 0.0;
	}

	Matrix4D Matrix4D::operator + (const Matrix4D & b) const
	{
		return Matrix4D();
	}

	Matrix4D Matrix4D::operator + (const Vector3D & v) const
	{
		Matrix4D r{ *this };

		r.c4r1 = c1r1 * v.x + c2r1 * v.y + c3r1 * v.z + c4r1;
		r.c4r2 = c1r2 * v.x + c2r2 * v.y + c3r2 * v.z + c4r2;
		r.c4r3 = c1r3 * v.x + c2r3 * v.y + c3r3 * v.z + c4r3;
		r.c4r4 = c1r4 * v.x + c2r4 * v.y + c3r4 * v.z + c4r4;

		return r;
	}

	Matrix4D Matrix4D::operator - (const Vector3D & v) const
	{
		return (*this) + (-v);
	}

	Matrix4D Matrix4D::operator - (const Matrix4D & b) const
	{
		return Matrix4D();
	}

	Matrix4D Matrix4D::operator * (float scale) const
	{
		return Matrix4D();
	}

	Matrix4D Matrix4D::operator * (const Matrix4D & b) const
	{
		return Matrix4D();
	}

	Matrix4D Matrix4D::operator * (const Vector3D & b) const
	{
		return Matrix4D();
	}

	Matrix4D Matrix4D::operator ~ () const
	{
		return {
			c1r1, c2r1, c3r1, c4r1,
			c1r2, c2r2, c3r2, c4r2,
			c1r3, c2r3, c3r3, c4r3,
			c1r4, c2r4, c3r4, c4r4
		};
	}

	bool Matrix4D::operator == (const Matrix4D & other) const
	{
		return c1r1 == other.c1r1 && c1r2 == other.c1r2 && c1r3 == other.c1r3 && c1r4 == other.c1r4 &&
			c2r1 == other.c2r1 && c2r2 == other.c2r2 && c2r3 == other.c2r3 && c2r4 == other.c2r4 &&
			c3r1 == other.c3r1 && c3r2 == other.c3r2 && c3r3 == other.c3r3 && c3r4 == other.c3r4 &&
			c4r1 == other.c4r1 && c4r2 == other.c4r2 && c4r3 == other.c4r3 && c4r4 == other.c4r4;
	}
}