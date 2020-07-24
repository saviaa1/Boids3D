#include "alignmentbehavior.hpp"

template <typename T>
vector3d<T> AlignmentBehavior<T>::compute(std::vector<Boid<T>> boids, Boid<T> myBoid, T visibility) {
    unsigned int neighborCount = 0;
    vector3d<T> velocity;

    for (auto boid : boids) {
        if (boid != myBoid) {
            if (boid.GetPosition().distance(myBoid.GetPosition()) < visibility) {
                velocity += boid->GetVelocity();
                neighborCount++;
            }
        }
    }
    if (neighborCount == 0) { return velocity; }
    velocity /= neighborCount;
    return velocity.normalize();
}