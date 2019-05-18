#include "pch.h"
#include <Matrix4D.h>
#include <cmath>
#include <Vector3D.h>
#include <Radians.h>

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
	const float f[16]{
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
	const float error{ 0.0000001f };

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

TEST(Matrix4D, MultiplyByMatrix)
{
	const Matrix4D a{
		1, 2, 3, 4,
		4, 3, 2, 1,
		1, 2, 3, 4,
		4, 3, 2, 1
	}, b{
		2, 2, 2, 2,
		3, 3, 3, 3,
		2, 2, 2, 2,
		3, 3, 3, 3
	};
	const Matrix4D m = a * b;

	EXPECT_FLOAT_EQ(1 * 2 + 4 * 2 + 1 * 2 + 4 * 2, m.c1r1);
	EXPECT_FLOAT_EQ(2 * 2 + 3 * 2 + 2 * 2 + 3 * 2, m.c1r2);
	EXPECT_FLOAT_EQ(3 * 2 + 2 * 2 + 3 * 2 + 2 * 2, m.c1r3);
	EXPECT_FLOAT_EQ(4 * 2 + 1 * 2 + 4 * 2 + 1 * 2, m.c1r4);

	EXPECT_FLOAT_EQ(1 * 3 + 4 * 3 + 1 * 3 + 4 * 3, m.c2r1);
	EXPECT_FLOAT_EQ(2 * 3 + 3 * 3 + 2 * 3 + 3 * 3, m.c2r2);
	EXPECT_FLOAT_EQ(3 * 3 + 2 * 3 + 3 * 3 + 2 * 3, m.c2r3);
	EXPECT_FLOAT_EQ(4 * 3 + 1 * 3 + 4 * 3 + 1 * 3, m.c2r4);

	EXPECT_FLOAT_EQ(1 * 2 + 4 * 2 + 1 * 2 + 4 * 2, m.c3r1);
	EXPECT_FLOAT_EQ(2 * 2 + 3 * 2 + 2 * 2 + 3 * 2, m.c3r2);
	EXPECT_FLOAT_EQ(3 * 2 + 2 * 2 + 3 * 2 + 2 * 2, m.c3r3);
	EXPECT_FLOAT_EQ(4 * 2 + 1 * 2 + 4 * 2 + 1 * 2, m.c3r4);

	EXPECT_FLOAT_EQ(1 * 3 + 4 * 3 + 1 * 3 + 4 * 3, m.c4r1);
	EXPECT_FLOAT_EQ(2 * 3 + 3 * 3 + 2 * 3 + 3 * 3, m.c4r2);
	EXPECT_FLOAT_EQ(3 * 3 + 2 * 3 + 3 * 3 + 2 * 3, m.c4r3);
	EXPECT_FLOAT_EQ(4 * 3 + 1 * 3 + 4 * 3 + 1 * 3, m.c4r4);
}

TEST(Matrix4D, Determinant)
{
	EXPECT_FLOAT_EQ(1, Matrix4D().determinant());

	const Matrix4D m{
		1, 3, 4, 10,
		2, 5, 9, 11,
		6, 8, 12, 15,
		7, 13, 14, 16
	};

	EXPECT_FLOAT_EQ(-594, m.determinant());
}


TEST(Matrix4D, Inverse)
{
	const Matrix4D a{
		1, 2, 4, 6,
		3, 1, 7, 10,
		5, 8, 1, 12,
		9, 11, 13, 1
	};
	bool success;
	const Matrix4D m = a.inverse(success);

	EXPECT_TRUE(success);

	EXPECT_FLOAT_EQ(-1643.0f / 2369, m.c1r1);
	EXPECT_FLOAT_EQ(744.0f / 2369, m.c1r2);
	EXPECT_FLOAT_EQ(194.0f / 2369, m.c1r3);
	EXPECT_FLOAT_EQ(90.0f / 2369, m.c1r4);

	EXPECT_FLOAT_EQ(816.0f / 2369, m.c2r1);
	EXPECT_FLOAT_EQ(-593.0f / 2369, m.c2r2);
	EXPECT_FLOAT_EQ(81.0f / 2369, m.c2r3);
	EXPECT_FLOAT_EQ(62.0f / 2369, m.c2r4);

	EXPECT_FLOAT_EQ(439.0f / 2369, m.c3r1);
	EXPECT_FLOAT_EQ(-20.0f / 2369, m.c3r2);
	EXPECT_FLOAT_EQ(-209.0f / 2369, m.c3r3);
	EXPECT_FLOAT_EQ(74.0f / 2369, m.c3r4);

	EXPECT_FLOAT_EQ(104.0f / 2369, m.c4r1);
	EXPECT_FLOAT_EQ(87.0f / 2369, m.c4r2);
	EXPECT_FLOAT_EQ(80.0f / 2369, m.c4r3);
	EXPECT_FLOAT_EQ(-85.0f / 2369, m.c4r4);
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
	std::make_tuple(90.0f, 0.0f, 0.0f, Vector3D(0, 1, 0), Vector3D(0, 0, 1)),
	std::make_tuple(90.0f, 0.0f, 0.0f, Vector3D(1, 0, 0), Vector3D(0, 0, -1)),
	std::make_tuple(90.0f, 0.0f, 0.0f, Vector3D(1, 0, 0), Vector3D(0, 1, 0))
));

TEST_P(RotateTest, Rotation)
{
	const std::tuple<float, float, float, Vector3D, Vector3D> tuple = GetParam();
	const float ax = std::get<0>(tuple),
		ay = std::get<1>(tuple),
		az = std::get<2>(tuple);
	const Vector3D v1 = std::get<3>(tuple);
	const Vector3D v2 = std::get<4>(tuple);
	const Matrix4D m = Matrix4D::rotation(
		Math::toRadians(ax),
		Math::toRadians(ay),
		Math::toRadians(az)
	);

	EXPECT_FLOAT_EQ(1, m.c1r1);
	EXPECT_FLOAT_EQ(0, m.c1r2);
	EXPECT_FLOAT_EQ(0, m.c1r3);
	EXPECT_FLOAT_EQ(0, m.c1r4);

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