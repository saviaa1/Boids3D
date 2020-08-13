#pragma once

#include "behavior.hpp"

template <typename T>
class AlignmentBehavior : public Behavior<T> {
public:
    AlignmentBehavior() {}
    virtual ~AlignmentBehavior() {}

    virtual vector3d<T> compute(std::vector<Boid<T>*>& boids, Boid<T>* myBoid, T viewDistance, T viewAngle) {
        unsigned int neighborCount = 0;
        vector3d<T> velocity;
        for (auto boid : boids) {
            if (boid != myBoid) {
                T tempDis = boid->GetPosition().distance(myBoid->GetPosition());
                T TempAng = myBoid->GetVelocity().angle(boid->GetPosition() - myBoid->GetPosition());
                //std::cout << TempAng << "; ";
                if (tempDis <= viewDistance && TempAng <= viewAngle) {
                    velocity += boid->GetVelocity();
                    neighborCount++;
                }
            }
        }
        if (neighborCount == 0) { return myBoid->GetVelocity(); }
        velocity /= neighborCount;
        if (velocity.isZero()) { return myBoid->GetVelocity(); }
        return velocity.normalize();
    }
};