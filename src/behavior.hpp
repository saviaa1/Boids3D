#pragma once

#include <vector>

#include "boid.hpp"
#include "vector3d.hpp"

template <typename T>
class Behavior {
public:
    Behavior() {};
    virtual ~Behavior() = 0;
    virtual compute() = 0;
private:
};
