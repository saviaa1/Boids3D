#pragma once

#include "behavior.hpp"

template <typename T>
class CombinedBehavior : public Behavior<T> {
public:
    CombinedBehavior() : Behavior<T>() {}
    CombinedBehavior(T _alignmentWeight, T _cohesionWeight, T _separationWeight)
        : alignmentWeight(_alignmentWeight), cohesionWeight(_cohesionWeight), separationWeight(_separationWeight) {}
    virtual ~CombinedBehavior() {}

    virtual vector3d<T> compute(USEDMAP<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* myBoid, T viewDistance, T viewAngle, T speed, int tick) {
        int neighborCount = 0;
        vector3d<T> alignmentForce, cohesionForce, separationForce;
        for (int i = 0; i < myBoid->nr; i++) {
            if (boidsHash.count(myBoid->neighbours[i]) > 0) {
                for (auto boid : boidsHash.at(myBoid->neighbours[i])) {
                    if (boid != myBoid) {
                        T tempDis = boid->GetPosition().distance(myBoid->GetPosition());
                        T tempAng = myBoid->GetVelocity().angle(boid->GetPosition() - myBoid->GetPosition());
                        if (tempDis <= viewDistance && tempAng <= viewAngle) {
                            alignmentForce += boid->GetVelocity();
                            cohesionForce += boid->GetPosition();
                            separationForce += boid->GetPosition() - myBoid->GetPosition();
                            neighborCount++;
                        }
                    }
                }
            }
        }
        //If neighborCount is 0, all force vectors are zero and a zero vector is returned.
        //If random movemend is wanted return something else here. Sine wave? Or create own behavior class for it.
        if (neighborCount == 0) {
            T tempSpeed = speed * (T) 0.02;
            //if (tempSpeed > 1) { tempSpeed = 1; }
            //If speed is below 0.5, return rand on only every N tick, otherwise return zero to reduce twitching. If speed over 0.5 return rand.
            if (tempSpeed < 0.5) {
                if (tick % 5 == 0) {
                    return this->getRand(myBoid) * tempSpeed;
                }
                return alignmentForce;
            }
            return this->getRand(myBoid) * tempSpeed;
        }

        alignmentForce /= (T) neighborCount;
        cohesionForce /= (T) neighborCount;
        separationForce /= (T) neighborCount;

        cohesionForce -= myBoid->GetPosition();
        separationForce *= -1;

        if (!alignmentForce.isZero()) { alignmentForce.normalize(); }
        if (!cohesionForce.isZero()) { cohesionForce.normalize(); }
        if (!separationForce.isZero()) { separationForce.normalize(); }

        return alignmentForce * alignmentWeight * (T) 0.01 + cohesionForce * cohesionWeight * (T) 0.01 + separationForce * separationWeight * (T) 0.01;
    }

    const T GetAligmentWeight() const { return alignmentWeight; }
    void SetAligmentWeight(T val) { alignmentWeight = val; }
    const T GetCohesionWeight() const { return cohesionWeight; }
    void SetCohesionWeight(T val) { cohesionWeight = val; }
    const T GetSeparationWeight() const { return separationWeight; }
    void SetSeparationWeight(T val) { separationWeight = val; }
private:
    T alignmentWeight = 1, cohesionWeight = 1, separationWeight = 1;
};