#include <gtest/gtest.h>
#include "../src/matrix.h"

class matrixTest : public ::testing::Test {
public:
//    matrixTest() {};

    void SetUp() override {};

    void TearDown() override {};
};

TEST_F(matrixTest, getSetTest) {
    matrix m = matrix(3, 2);
    m.setElement(0, 1, 3);
    m.setElement(2, 1, 7);
    EXPECT_EQ(m.getElement(0, 1), 3);
    EXPECT_EQ(m.getElement(2, 1), 7);
}

TEST_F(matrixTest, multiplyTest) {
    matrix m1 = matrix(2, 3);
    m1.setElement(0, 0, 3);
    m1.setElement(0, 1, -7);
    m1.setElement(0, 2, -1);
    m1.setElement(1, 0, 2);
    m1.setElement(1, 1, 1);
    m1.setElement(1, 2, 4);

    matrix m2 = matrix(3, 1);
    m2.setElement(0, 0, 4);
    m2.setElement(1, 0, -5);
    m2.setElement(2, 0, 2);

    matrix m3 = m1 *= m2;
    EXPECT_EQ(m3.getElement(0, 0), 45);
    EXPECT_EQ(m3.getElement(1, 0), 11);
}