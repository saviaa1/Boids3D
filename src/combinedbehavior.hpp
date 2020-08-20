#pragma once

#include "behavior.hpp"

template <typename T>
class CombinedBehavior : public Behavior<T> {
public:
    CombinedBehavior() {}
    virtual ~CombinedBehavior() {}

    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* myBoid, T viewDistance, T viewAngle, T alignmentWeight, T cohesionWeight, T seperationWeight) {
        unsigned int neighborCount = 0;
        vector3d<T> alignmentForce, cohesionForce, seperationForce;
        for (int i = 0; i < myBoid->nr; i++) {
            for (auto boid : boidsHash[myBoid->neighbours[i]]) {
                if (boid != myBoid) {
                    T tempDis = boid->GetPosition().distance(myBoid->GetPosition());
                    T TempAng = myBoid->GetVelocity().angle(boid->GetPosition() - myBoid->GetPosition());
                    if (tempDis <= viewDistance && TempAng <= viewAngle) {
                        alignmentForce += boid->GetVelocity();
                        cohesionForce += boid->GetPosition();
                        seperationForce += boid->GetPosition() - myBoid->GetPosition();
                        neighborCount++;
                    }
                }
            }
        }
        //If neighborCount is 0, all force vectors are zero and a zero vector is returned.
        //If random movemend is wanted return something else here. Sine wave? Or create own behavior class for it.
        if (neighborCount == 0) { return alignmentForce; }

        alignmentForce /= neighborCount;
        cohesionForce /= neighborCount;
        seperationForce /= neighborCount;

        cohesionForce -= myBoid->GetPosition();
        seperationForce *= -1;

        if (!alignmentForce.isZero()) { alignmentForce.normalize(); }
        if (!cohesionForce.isZero()) { cohesionForce.normalize(); }
        if (!seperationForce.isZero()) { seperationForce.normalize(); }

        return alignmentForce * alignmentWeight + cohesionForce * cohesionWeight + seperationForce * seperationWeight;
    }
};