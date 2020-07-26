#pragma once
#include <list>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "separationbehavior.hpp"
#include "cohesionbehavior.hpp"
#include "alignmentbehavior.hpp"

template <typename T>
class World {
    public:
        World(T aWeight, T cWeight, T sWeight, T distance, T s, T size)
            : alignmentWeight(aWeight), cohesionWeight(cWeight), separationWeight(sWeight), viewDistance(distance), speed(s), areaSize(size) {}
        ~World() {}

        void moveBoids() {
            //TODO: chainge behaviours to use behaviours list.
            SeparationBehavior<T> sep;
            CohesionBehavior<T> coh;
            AlignmentBehavior<T> ali;
            vector3d<T> velocity;
            for (auto boid : boids_) {
                velocity = (sep.compute(boids_, boid) * GetSeperationWeight()) + (coh.compute(boids_, boid) * GetCohesionWeight()) + (ali.compute(boids_, boid) * GetAligmentWeight());
                velocity.normalize();
                boid->SetNextVelAndPos(velocity * GetSpeed());
            }
            for (auto boid :  boids_) {
                boid->SetNextToCurrent();
            }
        }
        const T GetAligmentWeight() const { return alignmentWeight; }
        void SetAligmentWeight(T val) { alignmentWeight = val; }
        const T GetCohesionWeight() const { return cohesionWeight; }
        void SetCohesionWeight(T val) { cohesionWeight = val; }
        const T GetSeperationWeight() const { return separationWeight; }
        void SetSeperationWeight(T val) { separationWeight = val; }
        const T GetSpeed() const { return speed; }
        void SetSpeed(T val) { speed = val; }
        const T GetViewDistance() const { return viewDistance; }
        void SetViewDistance(T val) { viewDistance = val; }

    private:
        T alignmentWeight;
        T cohesionWeight;
        T separationWeight;
        T viewDistance;
        T speed;
        T areaSize;
        std::vector<Boid<T>*> boids_;
        int numberOfBoids;
        float viewAngle;

        //std::list<Behavior<T>> behaviors;
};