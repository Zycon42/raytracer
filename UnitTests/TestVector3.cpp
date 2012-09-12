#include <gtest/gtest.h>

#include "../Utils/Vector3.h"

class Vector3Test : public ::testing::Test 
{
protected:
	Vector3Test() : v(1.1f, 2.2f, 3.3f), u(0.5f, 3.1f, 1.6f) { }

	Vector3f v;
	Vector3f u;
};

TEST_F(Vector3Test, Basic) {
	EXPECT_FLOAT_EQ(1.1f, v.x());
	EXPECT_FLOAT_EQ(2.2f, v.y());
	EXPECT_FLOAT_EQ(3.3f, v.z());

	v.x() = 5.0f;
	EXPECT_FLOAT_EQ(5.0f, v.x());
	EXPECT_FLOAT_EQ(5.0f, v[0]);
}

TEST_F(Vector3Test, Operators) {
	float tmp[3] = {1.1f, 2.2f, 3.3f};
	ASSERT_TRUE(v == Vector3f(tmp));
	ASSERT_TRUE(v != Vector3f());

	EXPECT_EQ(Vector3f(-1.1f, -2.2f, -3.3f), -v);
	EXPECT_EQ(Vector3f(1.6f, 5.3f, 4.9f), v + u);
	EXPECT_EQ(Vector3f(0.6f, -0.9f, 1.7f), v - u);
	EXPECT_EQ(Vector3f(0.55f, 6.82f, 5.28f), v * u);
	EXPECT_EQ(Vector3i(2, 4, 6), Vector3i(1, 2, 3) * 2);
}

TEST_F(Vector3Test, Operations) {
	EXPECT_FLOAT_EQ(16.94f, v.lengthSquared());
	EXPECT_FLOAT_EQ(sqrt(16.94f), v.length());

	EXPECT_FLOAT_EQ(4.06f, v.distanceSquared(u));
	EXPECT_FLOAT_EQ(sqrt(4.06f), v.distance(u));

	EXPECT_FLOAT_EQ(12.65f, v.dot(u));
	EXPECT_EQ(Vector3f(-6.71f, -0.110000134f, 2.31f), v.cross(u));

	Vector3f tmp(v);
	tmp.normalize();
	EXPECT_FLOAT_EQ(1.0f, tmp.length());
	EXPECT_TRUE(tmp == v.normalizedCopy());
}
