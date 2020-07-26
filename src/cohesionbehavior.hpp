#pragma once

#include "behavior.hpp"

template <typename T>
class CohesionBehavior : public Behavior<T> {
public:
    CohesionBehavior() {}
    virtual ~CohesionBehavior() {}

    vector3d<T> compute(std::vector<Boid<T>> boids, Boid<T> myBoid, T visibility) {
        unsigned int neighborCount = 0;
        vector3d<T> position;

        for (auto boid : boids) {
            if (boid != myBoid) {
                if (boid.GetPosition().distance(myBoid.GetPosition()) < visibility) {
                    position += boid->GetPosition();
                    neighborCount++;
                }
            }
        }
        if (neighborCount == 0) { return position.normalize(); }
        position /= neighborCount;
        position -= myBoid.GetPosition();
        return position.normalize();
    }
};