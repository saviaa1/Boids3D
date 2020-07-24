#pragma once

#include "behavior.hpp"

template <typename T>
class AlignmentBehavior : public Behavior {
public:
    AlignmentBehavior() {}
    virtual ~AlignmentBehavior() {}

    vector3d<T> compute(std::vector<Boid<T>>, Boid<T>, T);
};