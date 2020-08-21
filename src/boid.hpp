#pragma once

#include <algorithm>

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
        nextVelocity = speedV;
    }
    //Adds given speed vector to pos.
    void SetNextPosition(vector3d<T> speedV, T areaSize) {
        nextPositio += speedV;
        /*if (nextPositio.X() < 0 || nextPositio.Y() < 0 || nextPositio.Z() < 0
            || nextPositio.X() > areaSize || nextPositio.Y() > areaSize || nextPositio.Z() > areaSize) {
            std::cout << "Out of area " << nextPositio;
        }*/
        //To make sure that boids do not go outside of the area.
        if (nextPositio.X() < 0) { nextPositio.X() = 0; }
        if (nextPositio.Y() < 0) { nextPositio.Y() = 0; }
        if (nextPositio.Z() < 0) { nextPositio.Z() = 0; }
        if (nextPositio.X() > areaSize-0.01) { nextPositio.X() = areaSize-0.01; }
        if (nextPositio.Y() > areaSize-0.01) { nextPositio.Y() = areaSize-0.01; }
        if (nextPositio.Z() > areaSize-0.01) { nextPositio.Z() = areaSize-0.01; }
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
    void SetCurrentHash(int& hash, int max) {
        currentHash_ = hash;
        nr = 0;
        hashesToCheck(neighbours, nr, max);
    }

    void hashesToCheck(int *hashesArray, int& nr, int max)
    {
        int i, j ,k;
        int c = 0;
        int x = currentHash_ & 0x3FF;
        int y = (currentHash_ >> 10) & 0x3FF;
        int z = (currentHash_ >> 20) & 0x3FF;

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
        if (positio == b.positio)
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
    vector3d<T> positio;
    vector3d<T> nextVelocity;
    vector3d<T> nextPositio;
    int currentHash_ = -1;
};
