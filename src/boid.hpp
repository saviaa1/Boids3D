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
    void SetNextPosition(vector3d<T> speedV, T areaSize) {
        nextPositio += speedV;
    }
    void SetNextToCurrent() {
        velocity = nextVelocity;
        positio = nextPositio;
    }
    // Hashing only works up to 1024x1024x1024 grids
    // so calling function needs to make sure gridSize is valid
    int CalculateHash(const T gridSize) {
        return (int) (positio.X() / gridSize) +
            (1 << 10) * (int) (positio.Y() / gridSize) +
            (1 << 20) * (int) (positio.Z() / gridSize);
    }
    int GetCurrentHash() const {
        return currentHash_;
    }
    void SetCurrentHash(int hash) {
        currentHash_ = hash;
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
    int currentHash_ = -1;

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