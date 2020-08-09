#pragma once

#include "behavior.hpp"

template <typename T>
class SeparationBehavior : public Behavior<T> {
public:
    SeparationBehavior() {}
    virtual ~SeparationBehavior() {}
    
    virtual vector3d<T> compute(std::vector<Boid<T>*> boids, Boid<T>* myBoid, T viewDistance) {
        unsigned int neighborCount = 0;
        vector3d<T> position;
        for (auto boid : boids) {
            if (boid != myBoid) {
                if (boid->GetPosition().distance(myBoid->GetPosition()) < viewDistance) {
                    position += boid->GetPosition() - myBoid->GetPosition();
                    neighborCount++;
                }
            }
        }
        if (neighborCount == 0) { return myBoid->GetVelocity(); }
        position /= neighborCount;
        position *= -1;
        if (position.isZero()) { return myBoid->GetVelocity(); }
        return position.normalize();
    }
};