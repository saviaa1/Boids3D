#pragma once

#include "behavior.hpp"

template <typename T>
class AvoidPredatorBehavior : public Behavior<T> {
public:
    AvoidPredatorBehavior() {}
    virtual ~AvoidPredatorBehavior() {}
    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>&, Boid<T>*, T, T, T, int) {
        return vector3d<T>();
    }
    virtual vector3d<T> computeA(Boid<T>* predator, Boid<T>* myBoid, T areaSize, T viewAngle) {
        vector3d<T> avoidPredatorForce;
        T tempDis = predator->GetPosition().distance(myBoid->GetPosition());
        //T tempAng = myBoid->GetVelocity().angle(predator->GetPosition() - myBoid->GetPosition());
        if (tempDis <= areaSize/2) { // && tempAng <= viewAngle
            //Gets a force vector from predator towards prey, aka direction to flee.
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
    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* predator, T viewDistance, T viewAngle, T speed, int tick) {
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
        if (!closestBoid) {
            //If speed is below 0.5, return rand on only every N tick, otherwise return zero. If speed over return rand.
            if (speed < 0.5) {
                if (tick % 5 == 0) {
                    return this->getRand(predator) * speed;
                }
                return pursueForce;
            }
            return this->getRand(predator) * speed;
        }
        pursueForce = closestBoid->GetPosition() - predator->GetPosition();
        if (!pursueForce.isZero()) { pursueForce.normalize(); }
        //std::cout << "In pursuit" << std::endl;
        return pursueForce;
    }
};