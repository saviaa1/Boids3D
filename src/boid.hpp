#pragma once

#include "vector3d.hpp"

template <typename T>
class Boid {
    public:
        Boid(const vector3d<T>& vel, const vector3d<T>& pos) : velocity(vel), positio(pos), nextVelocity(vel), nextPositio(pos) { }
        ~Boid() { }
        const vector3d<T>& GetVelocity() const { return velocity; }
        const vector3d<T>& GetPosition() const { return positio; }
        const vector3d<T>& GetNextVelocity() const { return nextVelocity; }
        const vector3d<T>& GetNextPosition() const { return nextPositio; }
        void SetNextVelAndPos(vector3d<T> speedV, T areaSize) {
            this->SetNextVelocity(speedV);
            this->SetNextPosition(nextVelocity, areaSize);
        }
        void SetNextVelocity(vector3d<T>& speedV) {
            if (!speedV.isZero()) {
                nextVelocity = speedV;
            }
        }
        //Adds given speed vector to pos.
        void SetNextPosition(vector3d<T>& speedV, T areaSize) {
            nextPositio += speedV;
            //Calc borders
            if (nextPositio.X() < 0) { nextPositio.X() *= -1; nextVelocity.X() *= -1; }
            if (nextPositio.Y() < 0) { nextPositio.Y() *= -1; nextVelocity.Y() *= -1; }
            if (nextPositio.Z() < 0) { nextPositio.Z() *= -1; nextVelocity.Z() *= -1; }

            if (nextPositio.X() > areaSize) { nextPositio.X() = areaSize - (nextPositio.X() - areaSize); nextVelocity.X() *= -1; }
            if (nextPositio.Y() > areaSize) { nextPositio.Y() = areaSize - (nextPositio.Y() - areaSize); nextVelocity.Y() *= -1; }
            if (nextPositio.Z() > areaSize) { nextPositio.Z() = areaSize - (nextPositio.Z() - areaSize); nextVelocity.Z() *= -1; }
        }
        void SetNextToCurrent() {
            velocity = nextVelocity;
            positio = nextPositio;
        }

    bool operator==(const Boid &b) const
    {
        if (positio == b.positio)
            return true;
        return false;
    }
    bool operator!=(const Boid &b) const
    {
        return !( (*this) == b );
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