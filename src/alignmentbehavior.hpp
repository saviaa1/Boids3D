#pragma once

#include "behavior.hpp"

template <typename T>
class AlignmentBehavior : public Behavior<T> {
public:
    AlignmentBehavior() {}
    virtual ~AlignmentBehavior() {}

    virtual vector3d<T> compute(std::vector<Boid<T>*> boids, Boid<T>* myBoid, T viewDistance) {
        unsigned int neighborCount = 0;
        vector3d<T> velocity;
        for (auto boid : boids) {
            if (boid != myBoid) {
                if (boid->GetPosition().distance(myBoid->GetPosition()) < viewDistance) {
                    velocity += boid->GetVelocity();
                    neighborCount++;
                }
            }
        }
        if (neighborCount == 0) { return velocity; }
        velocity /= neighborCount;
        if (velocity.isZero()) { return velocity; }
        return velocity.normalize();
    }
};