#pragma once

#include "behavior.hpp"

template <typename T>
class CohesionBehavior : public Behavior<T> {
public:
    CohesionBehavior() {}
    virtual ~CohesionBehavior() {}

    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash,
        int *hashesArray, int& nr, Boid<T>* myBoid, T viewDistance, T viewAngle) {
        unsigned int neighborCount = 0;
        vector3d<T> position;
        for (int i = 0; i < nr; i++) {
            for (auto boid : boidsHash[hashesArray[i]]) {
                if (boid != myBoid) {
                    T tempDis = boid->GetPosition().distance(myBoid->GetPosition());
                    T TempAng = myBoid->GetVelocity().angle(boid->GetPosition() - myBoid->GetPosition());
                    if (tempDis <= viewDistance && TempAng <= viewAngle) {
                        position += boid->GetPosition();
                        neighborCount++;
                    }
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