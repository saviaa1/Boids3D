#include "gtest/gtest.h"
#include "../src/world.hpp"

TEST(WorldTest, Creation) {
    World<float> world(1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 90.0f, 100.0f, 10);
    ASSERT_FLOAT_EQ(1.0f, world.GetAligmentWeight());
    ASSERT_FLOAT_EQ(2.0f, world.GetCohesionWeight());
    ASSERT_FLOAT_EQ(3.0f, world.GetSeperationWeight());
    ASSERT_FLOAT_EQ(4.0f, world.GetSpeed());
    ASSERT_FLOAT_EQ(10.0f, world.GetViewDistance());
    ASSERT_EQ(10, world.GetNumberOfBoids());
}

TEST(WorldTest, SetBehaviours) {
    World<float> world(1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 90.0f, 100.0f, 0);
    world.SetAligmentWeight(11.0f);
    world.SetCohesionWeight(12.23f);
    world.SetSeperationWeight(-13.3f);
    ASSERT_FLOAT_EQ(11.0f, world.GetAligmentWeight());
    ASSERT_FLOAT_EQ(12.23f, world.GetCohesionWeight());
    ASSERT_FLOAT_EQ(-13.3f, world.GetSeperationWeight());
}

TEST(WorldTest, SetSpeed) {
    World<float> world(1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 90.0f, 100.0f, 0);
    world.SetSpeed(-133.333f);
    ASSERT_FLOAT_EQ(-133.333f, world.GetSpeed());
}

TEST(WorldTest, SetViewDistance) {
    World<float> world(1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 90.0f, 100.0f, 0);
    world.SetViewDistance(100.0f);
    ASSERT_FLOAT_EQ(100.0f, world.GetViewDistance());
}

TEST(WorldTest, SetViewDistanceLessThan0) {
    World<float> world(1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 90.0f, 100.0f, 0);
    ASSERT_THROW(world.SetViewDistance(-100.0f), std::runtime_error);
}

TEST(WorldTest, AddBoid) {
    World<float> world(1.0f, 2.0f, 3.0f, 10.0f, 4.0f, 90.0f, 100.0f, 0);
    vector3d<float> aV, bV;
    Boid<float>* b = new Boid<float>(aV, bV);
    world.AddBoid(b);
    ASSERT_EQ(1, world.GetNumberOfBoids());
}

TEST(WorldTest, MoveBoid0) {
    World<float> world(1.0f, 1.0f, 1.0f, 100.0f, 1.0f, 90.0f, 100.0f, 0);
    vector3d<float> aV(1.0f, 2.0f , 3.0f), aP(1.0f, 1.0f, 1.0f);
    vector3d<float> bV(4.0f, 5.0f, 6.0f), bP(10.0f, 10.0f, 10.0f);
    vector3d<float> cV(7.0f, 8.0f, 9.0f), cP(15.0f, 15.0f, 15.0f);
    Boid<float>* a = new Boid<float>(aV, aV);
    Boid<float>* b = new Boid<float>(bV, bV);
    Boid<float>* c = new Boid<float>(cV, cV);
    world.AddBoid(a);
    world.AddBoid(b);
    world.AddBoid(c);
    world.moveBoids();
    ASSERT_EQ(3, world.GetNumberOfBoids());
}

TEST(WorldTest, MoveBoid1) {
    World<float> world(1.0f, 1.0f, 1.0f, 100.0f, 1.0f, 90.0f, 100.0f, 10);
    world.moveBoids();
    ASSERT_EQ(10, world.GetNumberOfBoids());
}

TEST(WorldTest, GetBoids) {
    World<float> world(1.0f, 1.0f, 1.0f, 100.0f, 1.0f, 90.0f, 100.0f, 10);
    ASSERT_EQ(10, world.GetBoids().size());
}