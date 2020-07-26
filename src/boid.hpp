#pragma once

#include "vector3d.hpp"

template <typename T>
class Boid
{
public:
    Boid(vector3d<T> vel, vector3d<T> pos)
        : velocity(vel), positio(pos) { std::cout << "HELLO_FROM_BOID" << std::endl; }
    ~Boid() { std::cout << "GOODBYE_FROM_BOID" << std::endl; }
    const vector3d<T> &GetVelocity() const { return velocity; }
    const vector3d<T> &GetPosition() const { return positio; }
    vector3d<T> &SetNextVelocity(vector3d<T> val) { nextVelocity = val; }
    vector3d<T> &SetNextPosition(vector3d<T> val) { nextPositio = val; }

    bool operator==(const Boid &b) const
    {
        if (positio == b.positio)
            return true;
        return false;
    }

private:
    vector3d<T> velocity;
    vector3d<T> positio;
    vector3d<T> nextVelocity;
    vector3d<T> nextPositio;

    /*
        float mass;
        //vector3D position;
        int positionIndex;
        //vector3D nextPosition;
        int nextPositionIndex;
        //vector3D velocity;
        float maxForce;
        float maxSpeed;
        //vector3D orientation;
        */
};