#pragma once

#include "behavior.hpp"

template <typename T>
class CohesionBehavior : public Behavior<T> {
public:
    CohesionBehavior() {}
    virtual ~CohesionBehavior() {}

    virtual vector3d<T> compute(std::vector<Boid<T>*> boids, Boid<T>* myBoid, T viewDistance) {
        unsigned int neighborCount = 0;
        vector3d<T> position;
        for (auto boid : boids) {
            if (boid != myBoid) {
                if (boid->GetPosition().distance(myBoid->GetPosition()) < viewDistance) {
                    position += boid->GetPosition();
                    neighborCount++;
                }
            }
        }
        if (neighborCount == 0) { return myBoid->GetVelocity(); }
        position /= neighborCount;
        position -= myBoid->GetPosition();
        if (position.isZero()) { return myBoid->GetVelocity(); }
        return position.normalize();
    }
};