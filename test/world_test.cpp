#include "gtest/gtest.h"
#include "../src/world.hpp"

TEST(WorldTest, Creation) {
    World<float> world(1, 2, 3, 10, 4, 90, 100, 10);
    ASSERT_FLOAT_EQ(1.0, world.GetAligmentWeight());
    ASSERT_FLOAT_EQ(2.0, world.GetCohesionWeight());
    ASSERT_FLOAT_EQ(3.0, world.GetSeperationWeight());
    ASSERT_FLOAT_EQ(4.0, world.GetSpeed());
    ASSERT_FLOAT_EQ(10.0, world.GetViewDistance());
    ASSERT_EQ(10, world.GetNumberOfBoids());
}

TEST(WorldTest, SetBehaviours) {
    World<float> world(1, 2, 3, 10, 4, 90, 100, 0);
    world.SetAligmentWeight(11);
    world.SetCohesionWeight(12.23);
    world.SetSeperationWeight(-13.3);
    ASSERT_FLOAT_EQ(11.0, world.GetAligmentWeight());
    ASSERT_FLOAT_EQ(12.23, world.GetCohesionWeight());
    ASSERT_FLOAT_EQ(-13.3, world.GetSeperationWeight());
}

TEST(WorldTest, SetSpeed) {
    World<float> world(1, 2, 3, 10, 4, 90, 100, 0);
    world.SetSpeed(-133.333);
    ASSERT_FLOAT_EQ(-133.333, world.GetSpeed());
}

TEST(WorldTest, SetViewDistance) {
    World<float> world(1, 2, 3, 10, 4, 90, 100, 0);
    world.SetViewDistance(100);
    ASSERT_FLOAT_EQ(100.0, world.GetViewDistance());
}

TEST(WorldTest, SetViewDistanceLessThan0) {
    World<float> world(1, 2, 3, 10, 4, 90, 100, 0);
    ASSERT_THROW(world.SetViewDistance(-100), std::runtime_error);
}

TEST(WorldTest, AddBoid) {
    World<float> world(1, 2, 3, 10, 4, 90, 100, 0);
    vector3d<float> aV, bV;
    Boid<float>* b = new Boid<float>(aV, bV);
    world.AddBoid(b);
    ASSERT_EQ(1, world.GetNumberOfBoids());
}

TEST(WorldTest, MoveBoid0) {
    World<float> world(1, 1, 1, 100, 1, 90, 100, 0);
    vector3d<float> aV(1,2,3), aP(1,1,1);
    vector3d<float> bV(4,5,6), bP(10,10,10);
    vector3d<float> cV(7,8,9), cP(15,15,15);
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
    World<float> world(1, 1, 1, 100, 1, 90, 100, 10);
    world.moveBoids();
    ASSERT_EQ(10, world.GetNumberOfBoids());
}

TEST(WorldTest, GetBoids) {
    World<float> world(1, 1, 1, 100, 1, 90, 100, 10);
    ASSERT_EQ(10, world.GetBoids().size());
}
