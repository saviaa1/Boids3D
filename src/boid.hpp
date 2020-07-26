#pragma once

#include "vector3d.hpp"

template <typename T>
class Boid {
    public:
        Boid() { std::cout << "HELLO_FROM_BOID" << std::endl; }
        ~Boid() { std::cout << "GOODBYE_FROM_BOID" << std::endl; }
        const vector3d<T>& GetVelocity() const { return velocity; }
        const vector3d<T>& GetPosition() const { return positio; }
        void SetNextVelAndPos(vector3d<T>& speedV, T areaSize) { this->SetNextVelocity(speedV); this->SetNextPosition(speedV, areaSize); }
        void SetNextVelocity(vector3d<T>& speedV) { nextVelocity = speedV; }
        void SetNextPosition(vector3d<T>& speedV, T areaSize) {
            nextPositio += speedV;
            //Calc borders
            if (nextPositio.x() < 0) { nextPositio.x() *= -1; nextVelocity.x() *= -1; }
            if (nextPositio.y() < 0) { nextPositio.y() *= -1; nextVelocity.y() *= -1; }
            if (nextPositio.z() < 0) { nextPositio.z() *= -1; nextVelocity.z() *= -1; }

            if (nextPositio.x() > areaSize) { nextPositio.x() = areaSize - (nextPositio.x() - areaSize); nextVelocity.x() *= -1; }
            if (nextPositio.y() > areaSize) { nextPositio.y() = areaSize - (nextPositio.y() - areaSize); nextVelocity.y() *= -1; }
            if (nextPositio.z() > areaSize) { nextPositio.z() = areaSize - (nextPositio.z() - areaSize); nextVelocity.z() *= -1; }
        }
        void SetNextToCurrent() {
            velocity = nextVelocity;
            positio = nextPositio;
        }

        bool operator==(const Boid& b) const {
            if (positio == b.positio) return true;
            return false;
        }

    private:
        vector3d<T>& velocity;
        vector3d<T>& positio;
        vector3d<T>& nextVelocity;
        vector3d<T>& nextPositio;

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