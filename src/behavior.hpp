#pragma once

#include <vector>

#include "boid.hpp"
#include "vector3d.hpp"

template <typename T>
class Behavior {
public:
    Behavior() {};
    virtual ~Behavior() {};
    virtual vector3d<T> compute(std::vector<Boid<T>*>&, Boid<T>*, T, T) = 0;
private:
    //T weight;
};
