#pragma once

#include "behavior.hpp"

template <typename T>
class CombinedBehavior : public Behavior<T> {
public:
    CombinedBehavior() : Behavior<T>() {}
    CombinedBehavior(T _alignmentWeight, T _cohesionWeight, T _seperationWeight)
        : alignmentWeight(_alignmentWeight), cohesionWeight(_cohesionWeight), seperationWeight(_seperationWeight) {}
    virtual ~CombinedBehavior() {}

    virtual vector3d<T> compute(std::map<int, std::vector<Boid<T>*>>& boidsHash, Boid<T>* myBoid, T viewDistance, T viewAngle) {
        int neighborCount = 0;
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
        if (neighborCount == 0) {
            return this->randRand();
            //return this->sineRand(myBoid);
        }

        alignmentForce /= (T) neighborCount;
        cohesionForce /= (T) neighborCount;
        seperationForce /= (T) neighborCount;

        cohesionForce -= myBoid->GetPosition();
        seperationForce *= -1;

        if (!alignmentForce.isZero()) { alignmentForce.normalize(); }
        if (!cohesionForce.isZero()) { cohesionForce.normalize(); }
        if (!seperationForce.isZero()) { seperationForce.normalize(); }

        return alignmentForce * alignmentWeight + cohesionForce * cohesionWeight + seperationForce * seperationWeight;
    }

    const T GetAligmentWeight() const { return alignmentWeight; }
    void SetAligmentWeight(T val) { alignmentWeight = val; }
    const T GetCohesionWeight() const { return cohesionWeight; }
    void SetCohesionWeight(T val) { cohesionWeight = val; }
    const T GetSeperationWeight() const { return seperationWeight; }
    void SetSeperationWeight(T val) { seperationWeight = val; }
private:
    T alignmentWeight = 1, cohesionWeight = 1, seperationWeight = 1;
};