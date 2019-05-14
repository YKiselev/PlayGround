#pragma once

#include "Vector3D.h"

namespace Math
{
	/*
		Column-oriented matrix
	*/
	struct Matrix4D
	{
		float c1r1, c1r2, c1r3, c1r4,
			c2r1, c2r2, c2r3, c2r4,
			c3r1, c3r2, c3r3, c3r4,
			c4r1, c4r2, c4r3, c4r4;

		Matrix4D();
		Matrix4D(const float src[16]);

		void orthographic(float left, float right, float top, float bottom, float near, float far);
		void perspective(float left, float right, float top, float bottom, float near, float far);
		void perspective(float fow, float ratio, float near, float far);
		void lookAt(Vector3f target, Vector3f eye, Vector3f up);

		Matrix4D operator + (const Matrix4D& b) const;
		//Matrix4D operator + (const Vector& v) const; // translate
		Matrix4D operator - (const Matrix4D& b) const;
		Matrix4D operator * (float scale) const;
		Matrix4D operator * (const Matrix4D& b) const;
		//Matrix4D operator * (const Vector& b) const;

		Matrix4D& operator ~ (); // transposition
		Matrix4D& rotate(float ax, float ay, float az);
		Matrix4D& inverse();

		double determinant() const;
	};

}