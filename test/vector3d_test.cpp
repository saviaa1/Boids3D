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
    ASSERT_FLOAT_EQ(0.0f, testE.X());
    ASSERT_FLOAT_EQ(0.0f, testE.Y());
    ASSERT_FLOAT_EQ(0.0f, testE.Z());
}
TEST(Vector3dTest, NonEmptyConstructorInt) {
    vector3d<int> testE(-1, 0, 1);
    ASSERT_EQ(-1, testE.X());
    ASSERT_EQ(0, testE.Y());
    ASSERT_EQ(1, testE.Z());
}
TEST(Vector3dTest, NonEmptyConstructorFloat) {
    vector3d<float> testE(-0.333f, 0.0f, 1.456f);
    ASSERT_FLOAT_EQ(-0.333f, testE.X());
    ASSERT_FLOAT_EQ(0.0f, testE.Y());
    ASSERT_FLOAT_EQ(1.456f, testE.Z());
}

TEST(Vector3dTest, CopyConstructFloat) {
    vector3d<float> b(-0.333f, 0.0f, 1.456f);
    vector3d<float> a(b);
    ASSERT_FLOAT_EQ(-0.333f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(1.456f, a.Z());
}

TEST(Vector3dTest, PlusFloat) {
    vector3d<float> a, b(-1.9f, 0.0f, 7.777f);
    a = a + b;
    ASSERT_FLOAT_EQ(-1.9f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(7.777f, a.Z());
}

TEST(Vector3dTest, PlusEqualFloat) {
    vector3d<float> a, b(-1.9f, 0.0f, 7.777f);
    a += b;
    ASSERT_FLOAT_EQ(-1.9f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(7.777f, a.Z());
}

TEST(Vector3dTest, MinusFloat) {
    vector3d<float> a, b(-1.9f, 0.0f, 7.777f);
    a = a - b;
    ASSERT_FLOAT_EQ(1.9f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(-7.777f, a.Z());
}

TEST(Vector3dTest, MinusEqualFloat) {
    vector3d<float> a, b(-1.9f, 0.0f, 7.777f);
    a -= b;
    ASSERT_FLOAT_EQ(1.9f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(-7.777f, a.Z());
}

TEST(Vector3dTest, MultipleFloat_Pos) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a = a * 2;
    ASSERT_FLOAT_EQ(-3.8f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(15.554f, a.Z());
}

TEST(Vector3dTest, MultipleFloat_Neg) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a = a * -2;
    ASSERT_FLOAT_EQ(3.8f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(-15.554f, a.Z());
}

TEST(Vector3dTest, MultipleEqualFloat_Pos) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a *= 2;
    ASSERT_FLOAT_EQ(-3.8f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(15.554f, a.Z());
}

TEST(Vector3dTest, MultipleEqualFloat_Neg) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a *= -2;
    ASSERT_FLOAT_EQ(3.8f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(-15.554f, a.Z());
}

TEST(Vector3dTest, Div_Pos) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a = a / 2;
    ASSERT_FLOAT_EQ(-0.95f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(3.8885f, a.Z());
}

TEST(Vector3dTest, Div_Neg) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a = a / -2;
    ASSERT_FLOAT_EQ(0.95f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(-3.8885f, a.Z());
}

TEST(Vector3dTest, Div_0) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    ASSERT_THROW(a/0, std::runtime_error);
}

TEST(Vector3dTest, DivEq_Pos) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a /= 2;
    ASSERT_FLOAT_EQ(-0.95f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(3.8885f, a.Z());
}

TEST(Vector3dTest, DivEq_Neg) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    a /= -2;
    ASSERT_FLOAT_EQ(0.95f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(-3.8885f, a.Z());
}

TEST(Vector3dTest, DivEq_0) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f);
    ASSERT_THROW(a/=0, std::runtime_error);
}

TEST(Vector3dTest, CopyFloat) {
    vector3d<float> a, b(-0.333f, 0.0f, 1.456f);
    a = b;
    ASSERT_FLOAT_EQ(-0.333f, a.X());
    ASSERT_FLOAT_EQ(0.0f, a.Y());
    ASSERT_FLOAT_EQ(1.456f, a.Z());
}

TEST(Vector3dTest, EqualsTrue) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f), b(-1.9f, 0.0f, 7.777f);
    ASSERT_TRUE(a==b);
}

TEST(Vector3dTest, EqualsFalse) {
    vector3d<float> a(-1.9f, 0.0f, 7.777f), b;
    ASSERT_FALSE(a==b);
}

TEST(Vector3dTest, Dot_product) {
    vector3d<float> a(0.0f, 3.0f, -7.0f), b(2.0f, 3.0f, 1.0f);
    ASSERT_FLOAT_EQ(2.0f, a.dot_product(b));
}

TEST(Vector3dTest, Magnitude) {
    vector3d<float> a(6.0f, 8.0f, 0.0f);
    ASSERT_FLOAT_EQ(10.0f, a.magnitude());
}

TEST(Vector3dTest, Distance) {
    vector3d<float> a(1.0f, 0.0f, -5.0f), b(-3.0f, 2.0f, -1.0f);
    ASSERT_FLOAT_EQ(6.0f, a.distance(b));
}

TEST(Vector3dTest, Normalize) {
    vector3d<float> a(2.0f, -4.0f, 1.0f);
    a.normalize();
    ASSERT_FLOAT_EQ(2.0f/sqrt(21.0f), a.X());
    ASSERT_FLOAT_EQ(-4.0f/sqrt(21.0f), a.Y());
    ASSERT_FLOAT_EQ(1.0f/sqrt(21.0f), a.Z());
}

TEST(Vector3dTest, Ostream) {
    vector3d<float> a(1.1f, 0.0f, -5.5f);
    std::ostringstream oss;
    oss << a;
    std::string b = oss.str();
    ASSERT_STREQ("vector3d(1.1, 0, -5.5)\n", b.c_str());
}

TEST(Vector3dTest, Angle) {
    static const float pi = acos(-1.0f);
    vector3d<float> a(-1.0f, 0.0f, 1.0f);
    vector3d<float> b = a.angle();
    ASSERT_FLOAT_EQ((135 * 2 * pi) / 360, b.X());
    ASSERT_FLOAT_EQ((90 * 2 * pi) / 360, b.Y());
    ASSERT_FLOAT_EQ((45 * 2 * pi) / 360, b.Z());
}
TEST(Vector3dTest, angleBetweenVec) {
    vector3d<float> a(5.0f, -20.0f, -14.0f);
    vector3d<float> b(-1.0f, 3.0f, 2.0f);

    ASSERT_FLOAT_EQ(175.87427f, a.angle(b));
}