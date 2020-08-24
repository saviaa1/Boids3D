#pragma once

#include "behavior.hpp"

template <typename T>
class AvoidPredatorBehavior : public Behavior<T> {
public:
    AvoidPredatorBehavior() {}
    virtual ~AvoidPredatorBehavior() {}
    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* predator, T viewDistance, T viewAngle) {
        return vector3d<T>();
    }
    virtual vector3d<T> computeA(Boid<T>* predator, Boid<T>* myBoid, T viewDistance, T viewAngle) {
        vector3d<T> avoidPredatorForce;
        T tempDis = predator->GetPosition().distance(myBoid->GetPosition());
        //T tempAng = myBoid->GetVelocity().angle(predator->GetPosition() - myBoid->GetPosition());
        if (tempDis <= viewDistance * 2) { // && tempAng <= viewAngle
            //Gets a force from predator towards prey.
            avoidPredatorForce = myBoid->GetPosition() - predator->GetPosition();
        }
        if (avoidPredatorForce.isZero()) { return avoidPredatorForce; }
        avoidPredatorForce.normalize();
        //std::cout << "Running" << std::endl;
        return avoidPredatorForce;
    }
};

template <typename T>
class PursueBoidsBehavior : public Behavior<T> {
public:
    PursueBoidsBehavior() {}
    virtual ~PursueBoidsBehavior() {}
    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* predator, T viewDistance, T viewAngle) {
        vector3d<T> pursueForce;
        Boid<T>* closestBoid = nullptr;
        T disToClosest = viewDistance * 2;
        for (int i = 0; i < predator->nr; i++) {
            for (auto boid : boidsHash[predator->neighbours[i]]) {
                if (boid != predator) {
                    T tempDis = boid->GetPosition().distance(predator->GetPosition());
                    //T tempAng = predator->GetVelocity().angle(boid->GetPosition() - predator->GetPosition());
                    if (tempDis <= disToClosest) { // && tempAng <= viewAngle
                        closestBoid = boid;
                        disToClosest = tempDis;
                    }
                }
            }
        }
        if (!closestBoid) { return this->randRand(); }
        pursueForce = closestBoid->GetPosition() - predator->GetPosition();
        if (!pursueForce.isZero()) { pursueForce.normalize(); }
        //std::cout << "In pursuit" << std::endl;
        return pursueForce;
    }
};