#include "gtest/gtest.h"

#include "../src/vector3d.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>


TEST(Vector3dTest, EmptyConstructDefTo_0Int) {
    vector3d<int> testE;
    ASSERT_EQ(0, testE.X());
    ASSERT_EQ(0, testE.Y());
    ASSERT_EQ(0, testE.Z());
}
TEST(Vector3dTest, EmptyConstructDefTo_0float) {
    vector3d<float> testE;
    ASSERT_FLOAT_EQ(0., testE.X());
    ASSERT_FLOAT_EQ(0., testE.Y());
    ASSERT_FLOAT_EQ(0., testE.Z());
}
TEST(Vector3dTest, NonEmptyConstructorInt) {
    vector3d<int> testE(-1, 0, 1);
    ASSERT_EQ(-1, testE.X());
    ASSERT_EQ(0, testE.Y());
    ASSERT_EQ(1, testE.Z());
}
TEST(Vector3dTest, NonEmptyConstructorFloat) {
    vector3d<float> testE(-0.333, 0.0, 1.456);
    ASSERT_FLOAT_EQ(-0.333, testE.X());
    ASSERT_FLOAT_EQ(0.0, testE.Y());
    ASSERT_FLOAT_EQ(1.456, testE.Z());
}

TEST(Vector3dTest, CopyConstructFloat) {
    vector3d<float> b(-0.333, 0.0, 1.456);
    vector3d<float> a(b);
    ASSERT_FLOAT_EQ(-0.333, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(1.456, a.Z());
}

TEST(Vector3dTest, PlusFloat) {
    vector3d<float> a, b(-1.9, 0.0, 7.777);
    a = a + b;
    ASSERT_FLOAT_EQ(-1.9, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(7.777, a.Z());
}

TEST(Vector3dTest, PlusEqualFloat) {
    vector3d<float> a, b(-1.9, 0.0, 7.777);
    a += b;
    ASSERT_FLOAT_EQ(-1.9, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(7.777, a.Z());
}

TEST(Vector3dTest, MinusFloat) {
    vector3d<float> a, b(-1.9, 0.0, 7.777);
    a = a - b;
    ASSERT_FLOAT_EQ(1.9, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(-7.777, a.Z());
}

TEST(Vector3dTest, MinusEqualFloat) {
    vector3d<float> a, b(-1.9, 0.0, 7.777);
    a -= b;
    ASSERT_FLOAT_EQ(1.9, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(-7.777, a.Z());
}

TEST(Vector3dTest, MultipleFloat_Pos) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a = a * 2;
    ASSERT_FLOAT_EQ(-3.8, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(15.554, a.Z());
}

TEST(Vector3dTest, MultipleFloat_Neg) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a = a * -2;
    ASSERT_FLOAT_EQ(3.8, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(-15.554, a.Z());
}

TEST(Vector3dTest, MultipleEqualFloat_Pos) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a *= 2;
    ASSERT_FLOAT_EQ(-3.8, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(15.554, a.Z());
}

TEST(Vector3dTest, MultipleEqualFloat_Neg) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a *= -2;
    ASSERT_FLOAT_EQ(3.8, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(-15.554, a.Z());
}

TEST(Vector3dTest, Div_Pos) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a = a / 2;
    ASSERT_FLOAT_EQ(-0.95, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(3.8885, a.Z());
}

TEST(Vector3dTest, Div_Neg) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a = a / -2;
    ASSERT_FLOAT_EQ(0.95, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(-3.8885, a.Z());
}

TEST(Vector3dTest, Div_0) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    ASSERT_THROW(a/0, std::runtime_error);
}

TEST(Vector3dTest, DivEq_Pos) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a /= 2;
    ASSERT_FLOAT_EQ(-0.95, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(3.8885, a.Z());
}

TEST(Vector3dTest, DivEq_Neg) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    a /= -2;
    ASSERT_FLOAT_EQ(0.95, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(-3.8885, a.Z());
}

TEST(Vector3dTest, DivEq_0) {
    vector3d<float> a(-1.9, 0.0, 7.777);
    ASSERT_THROW(a/=0, std::runtime_error);
}

TEST(Vector3dTest, CopyFloat) {
    vector3d<float> a, b(-0.333, 0.0, 1.456);
    a = b;
    ASSERT_FLOAT_EQ(-0.333, a.X());
    ASSERT_FLOAT_EQ(0.0, a.Y());
    ASSERT_FLOAT_EQ(1.456, a.Z());
}

TEST(Vector3dTest, EqualsTrue) {
    vector3d<float> a(-1.9, 0.0, 7.777), b(-1.9, 0.0, 7.777);
    ASSERT_TRUE(a==b);
}

TEST(Vector3dTest, EqualsFalse) {
    vector3d<float> a(-1.9, 0.0, 7.777), b;
    ASSERT_FALSE(a==b);
}

TEST(Vector3dTest, Dot_product) {
    vector3d<float> a(0.0, 3.0, -7.0), b(2.0, 3.0, 1.0);
    ASSERT_FLOAT_EQ(2.0, a.dot_product(b));
}

TEST(Vector3dTest, Magnitude) {
    vector3d<float> a(6.0, 8.0, 0.0);
    ASSERT_FLOAT_EQ(10.0, a.magnitude());
}

TEST(Vector3dTest, Distance) {
    vector3d<float> a(1.0, 0.0, -5.0), b(-3.0, 2.0, -1.0);
    ASSERT_FLOAT_EQ(6.0, a.distance(b));
}

TEST(Vector3dTest, Normalize) {
    vector3d<float> a(2,-4,1);
    a.normalize();
    ASSERT_FLOAT_EQ(2/sqrt(21), a.X());
    ASSERT_FLOAT_EQ(-4/sqrt(21), a.Y());
    ASSERT_FLOAT_EQ(1/sqrt(21), a.Z());
}

TEST(Vector3dTest, Ostream) {
    vector3d<float> a(1.1, 0.0, -5.5);
    std::ostringstream oss;
    oss << a;
    std::string b = oss.str();
    ASSERT_STREQ("vector3d(1.1, 0, -5.5)\n", b.c_str());
}

TEST(Vector3dTest, Angle) {
    vector3d<float> a(-1, 0, 1);
    vector3d<float> b = a.angle();
    ASSERT_FLOAT_EQ((135 * 2 * M_PI) / 360, b.X());
    ASSERT_FLOAT_EQ((90 * 2 * M_PI) / 360, b.Y());
    ASSERT_FLOAT_EQ((45 * 2 * M_PI) / 360, b.Z());
}
TEST(Vector3dTest, angleBetweenVec) {
    vector3d<float> a(5, -20, -14);
    vector3d<float> b(-1, 3, 2);

    ASSERT_FLOAT_EQ(175.87427, a.angle(b));
}