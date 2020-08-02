#pragma once

#include "behavior.hpp"

template <typename T>
class AvoidBordersBehavior : public Behavior<T> {
public:
    AvoidBordersBehavior() {}
    virtual ~AvoidBordersBehavior() {}

    vector3d<T> compute(Boid<T> myBoid, T areaMinSize, T areaMaxSize) {
        vector3d<T> velocity;
        if (myBoid.X() < areaMinSize) { velocity.X() += 10; }
        if (myBoid.Y() < areaMinSize) { velocity.Y() += 10; }
        if (myBoid.Z() < areaMinSize) { velocity.Z() += 10; }

        if (myBoid.X() > areaMaxSize) { velocity.X() -= 10; }
        if (myBoid.Y() > areaMaxSize) { velocity.Y() -= 10; }
        if (myBoid.Z() > areaMaxSize) { velocity.Z() -= 10; }
        return velocity;
    }
};