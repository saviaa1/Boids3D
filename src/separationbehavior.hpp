#pragma once

#include "behavior.hpp"

template <typename T>
class SeparationBehavior : public Behavior<T> {
public:
    SeparationBehavior() {}
    virtual ~SeparationBehavior() {}
    
    virtual vector3d<T> compute(std::vector<Boid<T>*>& boids, Boid<T>* myBoid, T viewDistance, T viewAngle) {
        unsigned int neighborCount = 0;
        vector3d<T> position;
        for (auto boid : boids) {
            if (boid != myBoid) {
                T tempDis = boid->GetPosition().distance(myBoid->GetPosition());
                T TempAng = myBoid->GetVelocity().angle(boid->GetPosition() - myBoid->GetPosition());
                if (tempDis <= viewDistance && TempAng <= viewAngle) {
                    position += boid->GetPosition() - myBoid->GetPosition();
                    neighborCount++;
                }
            }
        }
        if (neighborCount == 0) { return position; }
        position /= neighborCount;
        position *= -1;
        if (position.isZero()) { return position; }
        return position.normalize();
    }
};