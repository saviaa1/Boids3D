#include "gtest/gtest.h"
#include "../src/boid.hpp"

TEST(BoidTest, BoolEgTrue) {
    vector3d<float> aP(1.0f, 0.0f, -1.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);
    Boid<float> b(aV, aP);

    ASSERT_TRUE(a==b);
}

TEST(BoidTest, BoolEgFalse) {
    vector3d<float> aP(1.0f, 0.0f, -1.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);
    vector3d<float> bP(3.0f, 0.0f, -1.0f);
    vector3d<float> bV(-1.0f, 0.0f, 1.0f);
    Boid<float> b(bV, bP);

    ASSERT_FALSE(a==b) << a.GetPosition() << b.GetPosition();
}

TEST(BoidTest, GetVelocity) {
    vector3d<float> aP(1.0f, 0.0f, -1.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);

    ASSERT_EQ(aV, a.GetVelocity()) << a.GetVelocity();
}

TEST(BoidTest, GetPositio) {
    vector3d<float> aP(1.0f, 0.0f, -1.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);

    ASSERT_EQ(aP, a.GetPosition());
}

TEST(BoidTest, SetNextVel) {
    vector3d<float> aP(7.0f, 70.7f, 11.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);
    vector3d<float> nV(-3.0f, 0.0f, 3.0f);
    a.SetNextVelocity(nV);

    vector3d<float> rP(7.0f, 70.7f, 11.0f);
    vector3d<float> rV(-1.0f, 0.0f, 1.0f);
    vector3d<float> rNV(-3.0f, 0.0f, 3.0f);
    ASSERT_EQ(rV, a.GetVelocity());
    ASSERT_EQ(rP, a.GetPosition());
    ASSERT_EQ(rNV, a.GetNextVelocity());
}

TEST(BoidTest, SetNextPos) {
    vector3d<float> aP(7.0f, 70.7f, 11.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);
    vector3d<float> nV(-3.0f, 0.0f, 3.0f);
    a.SetNextPosition(nV, 100);


    vector3d<float> rP(7.0f, 70.7f, 11.0f);
    vector3d<float> rV(-1.0f, 0.0f, 1.0f);
    vector3d<float> rNP(4.0f, 70.7f, 14.0f);
    ASSERT_EQ(rV, a.GetVelocity());
    ASSERT_EQ(rP, a.GetPosition());
    ASSERT_EQ(rNP, a.GetNextPosition());
}

TEST(BoidTest, SetNextVelAndPos) {
    vector3d<float> aP(7.0f, 70.7f, 11.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);
    vector3d<float> nV(-3.0f, 0.0f, 3.0f);
    a.SetNextVelAndPos(nV, 1000);

    vector3d<float> rP(7.0f, 70.7f, 11.0f);
    vector3d<float> rV(-1.0f, 0.0f, 1.0f);
    vector3d<float> rNP(4.0f, 70.7f, 14.0f);
    vector3d<float> rNV(-3.0f, 0.0f, 3.0f);
    ASSERT_EQ(rV, a.GetVelocity());
    ASSERT_EQ(rP, a.GetPosition());
    ASSERT_EQ(rNP, a.GetNextPosition());
    ASSERT_EQ(rNV, a.GetNextVelocity());
}

TEST(BoidTest, SetNextToCurrent) {
    vector3d<float> aP(7.0f, 70.7f, 11.0f);
    vector3d<float> aV(-1.0f, 0.0f, 1.0f);
    Boid<float> a(aV, aP);
    vector3d<float> nV(-3.0f, 0.0f, 3.0f);
    a.SetNextVelAndPos(nV, 1000);
    a.SetNextToCurrent();

    vector3d<float> rP(4.0f, 70.7f, 14.0f);
    vector3d<float> rV(-3.0f, 0.0f, 3.0f);
    ASSERT_EQ(rV, a.GetVelocity());
    ASSERT_EQ(rP, a.GetPosition());
    ASSERT_EQ(rP, a.GetNextPosition());
    ASSERT_EQ(rV, a.GetNextVelocity());
}