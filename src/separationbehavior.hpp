#pragma once

#include <vector>

#include "behavior.hpp"
#include "vector3d.hpp"

template <typename T>
class SeparationBehavior : public Behavior {
public:
    SeparationBehavior() {}
    virtual ~SeparationBehavior() {}

    vector3d<T> compute(std::vector<Boid<T>>, Boid<T>, T);
};