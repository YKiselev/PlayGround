#include "pch.h"
#include <Matrix4D.h>
#include <cmath>
#include "Vector3D.h"

using Math::Matrix4D;
using Math::Vector3D;

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

//class LookAtParameters : public ::testing::TestWithParam<std::tuple<Vector3D, Vector3D, Vector3D>>
//{
//};
//
//INSTANTIATE_TEST_CASE_P(Matrix4D, LookAtParameters, ::testing::Values(
//	std::make_tuple(Vector3D(), Vector3D(), Vector3D()),
//	std::make_tuple(Vector3D(), Vector3D(), Vector3D()),
//	std::make_tuple(Vector3D(), Vector3D(), Vector3D()),
//	std::make_tuple(Vector3D(), Vector3D(), Vector3D()),
//	std::make_tuple(Vector3D(), Vector3D(), Vector3D())
//));


TEST(Matrix4D, LookAtPerspectiveProjection)
{
	//const std::tuple<Vector3D, Vector3D, Vector3D> t = GetParam();

	//const Vector3D target = std::get<0>(t), eye = std::get<1>(t), up = std::get<2>(t);

	const Matrix4D m;// = Matrix4D::lookAt(target, eye, up);

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

void testLookAt(Vector3D & target, Vector3D & eye, Vector3D & up)
{
	const Matrix4D m = Matrix4D::lookAt(target, eye, up);

	EXPECT_FLOAT_EQ(8, 8);
}

class RotateTest : public ::testing::TestWithParam<std::tuple<float, float, float, Vector3D, Vector3D>>
{
};

INSTANTIATE_TEST_CASE_P(Matrix4D, RotateTest, ::testing::Values(
	std::make_tuple(90.0f, 0.0f, 0.0f, Vector3D(), Vector3D()),
	std::make_tuple(90.0f, 0.0f, 0.0f, Vector3D(), Vector3D()),
	std::make_tuple(90.0f, 0.0f, 0.0f, Vector3D(), Vector3D())
));

TEST_P(RotateTest, Rotation)
{
	const std::tuple<float, float, float, Vector3D, Vector3D> tuple = GetParam();


}