#pragma once
#include <list>
#include <vector>
#include "behavior.hpp"
#include "boid.hpp"

class World
{
public:
    World();
    ~World();

    void moveBoids();

private:
    int numberOfBoids;
    float viewDistance;
    float viewAngle;
    std::vector<Boid> boids;
    std::list<Behavior> behaviors;
};