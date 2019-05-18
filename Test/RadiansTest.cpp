#include "pch.h"
#include <Radians.h>

TEST(Radians, ToRadians)
{
	EXPECT_FLOAT_EQ(0, Math::toRadians(0));
	EXPECT_FLOAT_EQ(Math::PI / 4, Math::toRadians(45));
	EXPECT_FLOAT_EQ(Math::PI / 2, Math::toRadians(90));
	EXPECT_FLOAT_EQ(3 * Math::PI / 4, Math::toRadians(135));
	EXPECT_FLOAT_EQ(Math::PI, Math::toRadians(180));
	EXPECT_FLOAT_EQ(5 * Math::PI / 4, Math::toRadians(225));
	EXPECT_FLOAT_EQ(3 * Math::PI / 2, Math::toRadians(270));
	EXPECT_FLOAT_EQ(7 * Math::PI / 4, Math::toRadians(315));
	EXPECT_FLOAT_EQ(2 * Math::PI, Math::toRadians(360));

	EXPECT_FLOAT_EQ(-Math::PI / 4, Math::toRadians(-45));
	EXPECT_FLOAT_EQ(-Math::PI / 2, Math::toRadians(-90));
	EXPECT_FLOAT_EQ(-3 * Math::PI / 4, Math::toRadians(-135));
	EXPECT_FLOAT_EQ(-Math::PI, Math::toRadians(-180));
	EXPECT_FLOAT_EQ(-5 * Math::PI / 4, Math::toRadians(-225));
	EXPECT_FLOAT_EQ(-3 * Math::PI / 2, Math::toRadians(-270));
	EXPECT_FLOAT_EQ(-7 * Math::PI / 4, Math::toRadians(-315));
	EXPECT_FLOAT_EQ(-2 * Math::PI, Math::toRadians(-360));
}

TEST(Radians, ToDegrees)
{
	EXPECT_FLOAT_EQ(0, Math::toDegrees(0));
	EXPECT_FLOAT_EQ(45, Math::toDegrees(Math::PI / 4));
	EXPECT_FLOAT_EQ(90, Math::toDegrees(Math::PI / 2));
	EXPECT_FLOAT_EQ(135, Math::toDegrees(3 * Math::PI / 4));
	EXPECT_FLOAT_EQ(180, Math::toDegrees(Math::PI));
	EXPECT_FLOAT_EQ(225, Math::toDegrees(5 * Math::PI / 4));
	EXPECT_FLOAT_EQ(270, Math::toDegrees(3 * Math::PI / 2));
	EXPECT_FLOAT_EQ(315, Math::toDegrees(7 * Math::PI / 4));
	EXPECT_FLOAT_EQ(360, Math::toDegrees(2 * Math::PI));

	EXPECT_FLOAT_EQ(-45, Math::toDegrees(-Math::PI / 4));
	EXPECT_FLOAT_EQ(-90, Math::toDegrees(-Math::PI / 2));
	EXPECT_FLOAT_EQ(-135, Math::toDegrees(-3 * Math::PI / 4));
	EXPECT_FLOAT_EQ(-180, Math::toDegrees(-Math::PI));
	EXPECT_FLOAT_EQ(-225, Math::toDegrees(-5 * Math::PI / 4));
	EXPECT_FLOAT_EQ(-270, Math::toDegrees(-3 * Math::PI / 2));
	EXPECT_FLOAT_EQ(-315, Math::toDegrees(-7 * Math::PI / 4));
	EXPECT_FLOAT_EQ(-360, Math::toDegrees(-2 * Math::PI));
}