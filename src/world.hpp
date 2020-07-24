#pragma once
#include <list>
#include <vector>
#include "behavior.hpp"
#include "boid.hpp"
#include "separationbehavior.hpp"
#include "cohesionbehavior.hpp"
#include "alignmentbehavior.hpp"

template <typename T>
class World
{
public:
    World();
    ~World();

    void moveBoids();
    const T GetAligmentWeight() const { return alignmentWeight; }
    void SetAligmentWeight(T val) { alignmentWeight = val; }
    const T GetCohesionWeight() const { return cohesionWeight; }
    void SetCohesionWeight(T val) { cohesionWeight = val; }
    const T GetSeperationWeight() const { return separationWeight; }
    void SetSeperationWeight(T val) { separationWeight = val; }
    const T GetSpeed() const { return speed; }
    void SetSpeed(T val) { speed = val; }
    const T GetViewDistance() const { return viewDistance; }
    void SetViewDistance(T val) { viewDistance = val; }

private:
    T alignmentWeight = 1;
    T cohesionWeight = 1;
    T separationWeight = 1;
    T viewDistance = 1;
    T speed = 10;
    std::vector<Boid<T>> boids;

    int numberOfBoids;
    float viewAngle;
    
    std::list<Behavior<T>> behaviors;
    
};