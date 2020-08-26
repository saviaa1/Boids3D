#pragma once

#include <vector>

#include "boid.hpp"
#include "vector3d.hpp"

template <typename T>
class Behavior {
public:
    Behavior() {}
    virtual ~Behavior() {}
    virtual vector3d<T> compute(USEDMAP<int, std::vector<Boid<T>*>>&, Boid<T>*, T, T, T, int) = 0;

    vector3d<T> getRand(Boid<T>* myboid) {
        if (randActive) {
            return randRand();
        }
        return vector3d<T>();
    }

    vector3d<T> sineRand(Boid<T>* myBoid) {
        static const float pi = acos(-1.0f);
        T x = 0.2 * std::cos(myBoid->GetPosition().cX() * pi / 60);
        vector3d<T> ret(x, x, x);
        //std::cout << "Sine: " << ret;
        return ret;
    }
    vector3d<T> randRand() {
        std::random_device random_device;
        std::mt19937 rng(random_device());
        std::uniform_real_distribution<T> dist((T) -0.2, (T) 0.2);
        vector3d<T> ret(dist(rng), dist(rng), dist(rng));
        return ret;
    }

    void setRandStatus(bool val) {
        randActive = val;
    }
    const bool getRandStatus() const  {
        return randActive;
    }
private:
    bool randActive = true;
};
