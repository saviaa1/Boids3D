#pragma once

#include "behavior.hpp"

template <typename T>
class CohesionBehavior : public Behavior {
public:
    CohesionBehavior() {}
    virtual ~CohesionBehavior() {}

    vector3d<T> compute(std::vector<Boid<T>>, Boid<T>, T);
};