#pragma once

#include "behavior.hpp"

template <typename T>
class AvoidBordersBehavior : public Behavior<T> {
public:
    AvoidBordersBehavior() {}
    virtual ~AvoidBordersBehavior() {}

    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* myBoid, T viewDistance, T areaSize) {
        vector3d<T> force, pos = myBoid->GetPosition();
        if (pos.X() < viewDistance) { force.X() = 1; }
        if (pos.Y() < viewDistance) { force.Y() = 1; }
        if (pos.Z() < viewDistance) { force.Z() = 1; }

        if (pos.X() > areaSize - viewDistance) { force.X() = -1; }
        if (pos.Y() > areaSize - viewDistance) { force.Y() = -1; }
        if (pos.Z() > areaSize - viewDistance) { force.Z() = -1; }
        return force;
    }
};