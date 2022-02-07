#include <gtest/gtest.h>
#include "../src/georeference.h"

constexpr double EPSILON = 0.00001;

class georeferenceTest : public ::testing::Test {
public:
//    georeferenceTest() {};

    void SetUp() override {};

    void TearDown() override {};
};

TEST_F(georeferenceTest, intersectionTest) {
    Vector vector = Vector(2, -3, -4);
    Point3 point3 = Point3(4, 2, 2);
    Plane plane = Plane(Vector(1, 2, 2), Point3(4, 3, 2));
    Point3 result = plane.intersection(vector, point3);
    EXPECT_NEAR(3.667, result.getX(), EPSILON);
    EXPECT_NEAR(2.500, result.getY(), EPSILON);
    EXPECT_NEAR(2.667, result.getZ(), EPSILON);
}

TEST_F(georeferenceTest, ecefToLlhTest) {
    Point3 point3 = Point3(4021113, 3618157, 3369362);
    Point3 result = EcefToLlh(point3);
    EXPECT_NEAR(32.09108, result.getX(), EPSILON);
    EXPECT_NEAR(41.98056, result.getY(), EPSILON);
}