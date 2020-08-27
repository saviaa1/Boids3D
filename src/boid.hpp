#pragma once

#include <algorithm>

#include "vector3d.hpp"

template <typename T>
class Boid {
public:
    Boid(const vector3d<T>& vel, const vector3d<T>& pos) : velocity(vel), position(pos), nextVelocity(vel), nextPosition(pos) { }
    ~Boid() { }
    const vector3d<T>& GetVelocity() const { return velocity; }
    const vector3d<T>& GetPosition() const { return position; }
    const vector3d<T>& GetNextVelocity() const { return nextVelocity; }
    const vector3d<T>& GetNextPosition() const { return nextPosition; }
    void SetNextVelAndPos(vector3d<T> speedV, T areaSize) {
        this->SetNextVelocity(speedV);
        this->SetNextPosition(nextVelocity, areaSize);
    }
    void SetNextVelocity(vector3d<T>& speedV) {
        nextVelocity = speedV;
    }
    //Adds given speed vector to pos.
    void SetNextPosition(vector3d<T> speedV, T areaSize) {
        nextPosition += speedV;
        //To make sure that boids do not go outside of the area.
        if (nextPosition.X() < 0.0f) { nextPosition.X() = 0.0f; }
        if (nextPosition.Y() < 0.0f) { nextPosition.Y() = 0.0f; }
        if (nextPosition.Z() < 0.0f) { nextPosition.Z() = 0.0f; }
        if (nextPosition.X() > areaSize-0.01f) { nextPosition.X() = areaSize-0.01f; }
        if (nextPosition.Y() > areaSize-0.01f) { nextPosition.Y() = areaSize-0.01f; }
        if (nextPosition.Z() > areaSize-0.01f) { nextPosition.Z() = areaSize-0.01f; }
    }
    void SetNextToCurrent() {
        velocity = nextVelocity;
        position = nextPosition;
    }
    // Hashing only works up to 1024x1024x1024 grids
    // so calling function needs to make sure gridSize is valid
    int CalculateHash(const T gridSize) {
        return (int) (position.X() / gridSize) +
            (1 << 10) * (int) (position.Y() / gridSize) +
            (1 << 20) * (int) (position.Z() / gridSize);
    }
    int GetCurrentHash() const {
        return currentHash;
    }
    void SetCurrentHash(int& hash, int max) {
        currentHash = hash;
        nr = 0;
        hashesToCheck(neighbours, nr, max);
    }

    void hashesToCheck(int *hashesArray, int& nr, int max)
    {
        int i, j ,k;
        int c = 0;
        int x = currentHash & 0x3FF;
        int y = (currentHash >> 10) & 0x3FF;
        int z = (currentHash >> 20) & 0x3FF;

        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                for (k = -1; k <= 1; k++) {
                    if (x + i >= 0 && y + j >= 0 && z + k >= 0 && x + i < max && y + j < max && z + k) {
                        hashesArray[nr++] = x + i + (y + j) * (1 << 10) + (z + k) * (1 << 20);
                    }
                }
            }
        }
    }

    bool operator==(const Boid &b) const
    {
        if (position == b.position)
            return true;
        return false;
    }
    bool operator!=(const Boid &b) const
    {
        return !( (*this) == b );
    }

    int neighbours[27]; // 3 * 3 * 3 grid size
    int nr;

private:
    vector3d<T> velocity;
    vector3d<T> position;
    vector3d<T> nextVelocity;
    vector3d<T> nextPosition;
    int currentHash = -1;
};
