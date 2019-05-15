#include "pch.h"
#include <Matrix4D.h>
#include <cmath>

using Math::Matrix4D;

TEST(Matrix4D, Identity)
{
	const Matrix4D m;

	EXPECT_FLOAT_EQ(1, m.c1r1);
	EXPECT_FLOAT_EQ(0, m.c1r2);
	EXPECT_FLOAT_EQ(0, m.c1r3);
	EXPECT_FLOAT_EQ(0, m.c1r4);

	EXPECT_FLOAT_EQ(0, m.c2r1);
	EXPECT_FLOAT_EQ(1, m.c2r2);
	EXPECT_FLOAT_EQ(0, m.c2r3);
	EXPECT_FLOAT_EQ(0, m.c2r4);

	EXPECT_FLOAT_EQ(0, m.c3r1);
	EXPECT_FLOAT_EQ(0, m.c3r2);
	EXPECT_FLOAT_EQ(1, m.c3r3);
	EXPECT_FLOAT_EQ(0, m.c3r4);

	EXPECT_FLOAT_EQ(0, m.c4r1);
	EXPECT_FLOAT_EQ(0, m.c4r2);
	EXPECT_FLOAT_EQ(0, m.c4r3);
	EXPECT_FLOAT_EQ(1, m.c4r4);
}

TEST(Matrix4D, CreatesFromArray)
{
	const float f[16] = {
		1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
	};

	const Matrix4D m(f);

	EXPECT_FLOAT_EQ(1, m.c1r1);
	EXPECT_FLOAT_EQ(2, m.c1r2);
	EXPECT_FLOAT_EQ(3, m.c1r3);
	EXPECT_FLOAT_EQ(4, m.c1r4);

	EXPECT_FLOAT_EQ(5, m.c2r1);
	EXPECT_FLOAT_EQ(6, m.c2r2);
	EXPECT_FLOAT_EQ(7, m.c2r3);
	EXPECT_FLOAT_EQ(8, m.c2r4);

	EXPECT_FLOAT_EQ(9, m.c3r1);
	EXPECT_FLOAT_EQ(10, m.c3r2);
	EXPECT_FLOAT_EQ(11, m.c3r3);
	EXPECT_FLOAT_EQ(12, m.c3r4);

	EXPECT_FLOAT_EQ(13, m.c4r1);
	EXPECT_FLOAT_EQ(14, m.c4r2);
	EXPECT_FLOAT_EQ(15, m.c4r3);
	EXPECT_FLOAT_EQ(16, m.c4r4);
}

TEST(Matrix4D, Creation)
{
	const Matrix4D m(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	EXPECT_FLOAT_EQ(1, m.c1r1);
	EXPECT_FLOAT_EQ(2, m.c1r2);
	EXPECT_FLOAT_EQ(3, m.c1r3);
	EXPECT_FLOAT_EQ(4, m.c1r4);

	EXPECT_FLOAT_EQ(5, m.c2r1);
	EXPECT_FLOAT_EQ(6, m.c2r2);
	EXPECT_FLOAT_EQ(7, m.c2r3);
	EXPECT_FLOAT_EQ(8, m.c2r4);

	EXPECT_FLOAT_EQ(9, m.c3r1);
	EXPECT_FLOAT_EQ(10, m.c3r2);
	EXPECT_FLOAT_EQ(11, m.c3r3);
	EXPECT_FLOAT_EQ(12, m.c3r4);

	EXPECT_FLOAT_EQ(13, m.c4r1);
	EXPECT_FLOAT_EQ(14, m.c4r2);
	EXPECT_FLOAT_EQ(15, m.c4r3);
	EXPECT_FLOAT_EQ(16, m.c4r4);
}

TEST(Matrix4D, OrthogrtaphicProjection)
{
	const float left = 0,
		right = 100,
		top = 200,
		bottom = 0,
		near = -1,
		far = 1;

	const Matrix4D m = Matrix4D::orthographic(left, right, top, bottom, near, far);

	EXPECT_FLOAT_EQ(2 / (right - left), m.c1r1);
	EXPECT_FLOAT_EQ(0, m.c1r2);
	EXPECT_FLOAT_EQ(0, m.c1r3);
	EXPECT_FLOAT_EQ(0, m.c1r4);

	EXPECT_FLOAT_EQ(0, m.c2r1);
	EXPECT_FLOAT_EQ(2 / (top - bottom), m.c2r2);
	EXPECT_FLOAT_EQ(0, m.c2r3);
	EXPECT_FLOAT_EQ(0, m.c2r4);

	EXPECT_FLOAT_EQ(0, m.c3r1);
	EXPECT_FLOAT_EQ(0, m.c3r2);
	EXPECT_FLOAT_EQ(-2 / (far - near), m.c3r3);
	EXPECT_FLOAT_EQ(0, m.c3r4);

	EXPECT_FLOAT_EQ(-(right + left) / (right - left), m.c4r1);
	EXPECT_FLOAT_EQ(-(top + bottom) / (top - bottom), m.c4r2);
	EXPECT_FLOAT_EQ(-(far + near) / (far - near), m.c4r3);
	EXPECT_FLOAT_EQ(1, m.c4r4);
}

TEST(Matrix4D, LeftRightTopBottomPerspectiveProjection)
{
	const float left = 0,
		right = 100,
		top = 200,
		bottom = 0,
		near = -1,
		far = 1;

	const Matrix4D m = Matrix4D::perspective(left, right, top, bottom, near, far);

	EXPECT_FLOAT_EQ(2 * near / (right - left), m.c1r1);
	EXPECT_FLOAT_EQ(0, m.c1r2);
	EXPECT_FLOAT_EQ(0, m.c1r3);
	EXPECT_FLOAT_EQ(0, m.c1r4);

	EXPECT_FLOAT_EQ(0, m.c2r1);
	EXPECT_FLOAT_EQ(2 * near / (top - bottom), m.c2r2);
	EXPECT_FLOAT_EQ(0, m.c2r3);
	EXPECT_FLOAT_EQ(0, m.c2r4);

	EXPECT_FLOAT_EQ((right + left) / (right - left), m.c3r1);
	EXPECT_FLOAT_EQ((top + bottom) / (top - bottom), m.c3r2);
	EXPECT_FLOAT_EQ(-(far + near) / (far - near), m.c3r3);
	EXPECT_FLOAT_EQ(-1, m.c3r4);

	EXPECT_FLOAT_EQ(0, m.c4r1);
	EXPECT_FLOAT_EQ(0, m.c4r2);
	EXPECT_FLOAT_EQ(-2 * far * near / (far - near), m.c4r3);
	EXPECT_FLOAT_EQ(0, m.c4r4);
}

TEST(Matrix4D, FovPerspectiveProjection)
{
	const float left = -5,
		right = 5,
		top = 10,
		bottom = -10,
		near = -1,
		far = 1;

	const Matrix4D m = Matrix4D::perspective(2 * std::atan(-left / near), 0.5, near, far);
	const float error = 0.0000001;

	EXPECT_NEAR(2.0 * near / (right - left), m.c1r1, error);
	EXPECT_FLOAT_EQ(0, m.c1r2);
	EXPECT_FLOAT_EQ(0, m.c1r3);
	EXPECT_FLOAT_EQ(0, m.c1r4);

	EXPECT_FLOAT_EQ(0, m.c2r1);
	EXPECT_NEAR(2.0 * near / (top - bottom), m.c2r2, error);
	EXPECT_FLOAT_EQ(0, m.c2r3);
	EXPECT_FLOAT_EQ(0, m.c2r4);

	EXPECT_NEAR((right + left) / (right - left), m.c3r1, error);
	EXPECT_NEAR((top + bottom) / (top - bottom), m.c3r2, error);
	EXPECT_NEAR(-(far + near) / (far - near), m.c3r3, error);
	EXPECT_FLOAT_EQ(-1, m.c3r4);

	EXPECT_FLOAT_EQ(0, m.c4r1);
	EXPECT_FLOAT_EQ(0, m.c4r2);
	EXPECT_NEAR(-2.0 * far * near / (far - near), m.c4r3, error);
	EXPECT_FLOAT_EQ(0, m.c4r4);
}

TEST(Matrix4D, Transposes)
{
	const Matrix4D m = ~Matrix4D(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	EXPECT_FLOAT_EQ(1, m.c1r1);
	EXPECT_FLOAT_EQ(5, m.c1r2);
	EXPECT_FLOAT_EQ(9, m.c1r3);
	EXPECT_FLOAT_EQ(13, m.c1r4);

	EXPECT_FLOAT_EQ(2, m.c2r1);
	EXPECT_FLOAT_EQ(6, m.c2r2);
	EXPECT_FLOAT_EQ(10, m.c2r3);
	EXPECT_FLOAT_EQ(14, m.c2r4);

	EXPECT_FLOAT_EQ(3, m.c3r1);
	EXPECT_FLOAT_EQ(7, m.c3r2);
	EXPECT_FLOAT_EQ(11, m.c3r3);
	EXPECT_FLOAT_EQ(15, m.c3r4);

	EXPECT_FLOAT_EQ(4, m.c4r1);
	EXPECT_FLOAT_EQ(8, m.c4r2);
	EXPECT_FLOAT_EQ(12, m.c4r3);
	EXPECT_FLOAT_EQ(16, m.c4r4);
}

TEST(Matrix4D, LookAtPerspectiveProjection)
{
	const Matrix4D m = Matrix4D::lookAt();

	EXPECT_FLOAT_EQ(1, m.c1r1);
	EXPECT_FLOAT_EQ(5, m.c1r2);
	EXPECT_FLOAT_EQ(9, m.c1r3);
	EXPECT_FLOAT_EQ(13, m.c1r4);

	EXPECT_FLOAT_EQ(2, m.c2r1);
	EXPECT_FLOAT_EQ(6, m.c2r2);
	EXPECT_FLOAT_EQ(10, m.c2r3);
	EXPECT_FLOAT_EQ(14, m.c2r4);

	EXPECT_FLOAT_EQ(3, m.c3r1);
	EXPECT_FLOAT_EQ(7, m.c3r2);
	EXPECT_FLOAT_EQ(11, m.c3r3);
	EXPECT_FLOAT_EQ(15, m.c3r4);

	EXPECT_FLOAT_EQ(4, m.c4r1);
	EXPECT_FLOAT_EQ(8, m.c4r2);
	EXPECT_FLOAT_EQ(12, m.c4r3);
	EXPECT_FLOAT_EQ(16, m.c4r4);
}
