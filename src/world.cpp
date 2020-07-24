#include "world.hpp"

template <typename T>
World<T>::World() {
}
template <typename T>
World<T>::~World() {
}
template <typename T>
void World<T>::moveBoids() {
    //TODO: chainge behaviours to use behaviours list.
    SeparationBehavior<T> sep;
    CohesionBehavior<T> coh;
    AlignmentBehavior<T> ali;
    vector3d<T> velocity;
    for (auto boid : boids) {
        velocity = (sep.compute(boids, boid) * GetSeperationWeight()) + (coh.compute(boids, boid) * GetCohesionWeight()) + (ali.compute(boids, boid) * GetAligmentWeight());
        velocity.normalize();
        boid->SetNextVelocity(velocity * GetSpeed());
    }
}