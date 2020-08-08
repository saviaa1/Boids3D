#pragma once
#include <list>
#include <vector>
#include <map>
#include <stdexcept>
#include <random>
#include <algorithm>

#include "boid.hpp"
#include "behavior.hpp"
#include "separationbehavior.hpp"
#include "cohesionbehavior.hpp"
#include "alignmentbehavior.hpp"

template <typename T>
class World {
    public:
        World(T _alignmentWeight, T _cohesionWeight, T _separationWeight, T _viewDistance, T _boidSpeed, T _viewAngle, T _areaSize, int _numberOfBoids)
            : alignmentWeight(_alignmentWeight), cohesionWeight(_cohesionWeight), separationWeight(_separationWeight), viewDistance(_viewDistance), boidSpeed(_boidSpeed), viewAngle(_viewAngle), areaSize(_areaSize) {
                initBoids(_numberOfBoids);
                SetGridSize(_viewDistance, _areaSize);
            }
        ~World() {
            for (auto boid : boids_) {
                delete boid;
            }
        }

        //uniform_real_distribution defined on float, double and long double. If others types are needed templates partial specialization is needed.
        void initBoids(int numberOfBoids) {
            //Currently generates same sequence every time, if more random is wanted, uncomment next two lines and comment third.
            //std::random_device random_device;
            //std::mt19937 rng(random_device());
            std::mt19937 rng;
            std::uniform_real_distribution<T> zeroToSize(0, areaSize);

            for (auto i = 0; i < numberOfBoids; i++) {
                vector3d<T> speedV(zeroToSize(rng), zeroToSize(rng), zeroToSize(rng)),
                            posV(zeroToSize(rng), zeroToSize(rng), zeroToSize(rng));
                //std::cout << speedV << posV << "..\n";
                if (!speedV.isZero()) { speedV.normalize(); }
                Boid<T>* b = new Boid<T>(speedV, posV);
                AddBoid(b);
            }
        }
        void AddBoid(Boid<T>* b) {
            boids_.push_back(b);
        }
        const size_t GetNumberOfBoids() const {
            return boids_.size();
        }
        const std::vector<Boid<T>*> &GetBoids() const {
            return boids_;
        }
        void moveBoids() {
            //TODO: chainge behaviours to use behaviours list.
            SeparationBehavior<T> sep;
            CohesionBehavior<T> coh;
            AlignmentBehavior<T> ali;
            vector3d<T> velocity;
            for (auto boid : boids_) {
                velocity = (sep.compute(boids_, boid, viewDistance) * separationWeight)
                    + (coh.compute(boids_, boid, viewDistance) * cohesionWeight)
                    + (ali.compute(boids_, boid, viewDistance) * alignmentWeight);
                if (!velocity.isZero()) { velocity.normalize(); }
                //std::cout << velocity << std::endl;
                boid->SetNextVelAndPos(velocity * boidSpeed, areaSize);
            }
            int oldHash, newHash;
            for (auto boid :  boids_) {
                boid->SetNextToCurrent();
                oldHash = boid->GetCurrentHash();
                newHash = boid->CalculateHash(gridSize);
                if (newHash != oldHash) {
                    boidsHash_[oldHash].erase(std::remove(boidsHash_[oldHash].begin(), boidsHash_[oldHash].end(), boid), boidsHash_[oldHash].end());
                    //std::vector<Boid*>::erase(boidsHash_[oldHash], boid);
                    if (boidsHash_.count(newHash) == 0) {
                        std::list<Boid<T>*> blist;
                        //boidsHash_.emplace(newHash, blist);
                    }
                    boidsHash_[newHash].push_back(boid);
                    boid->SetCurrentHash(newHash);
                }
            }
        }
        const T GetAligmentWeight() const { return alignmentWeight; }
        void SetAligmentWeight(T val) { alignmentWeight = val; }
        const T GetCohesionWeight() const { return cohesionWeight; }
        void SetCohesionWeight(T val) { cohesionWeight = val; }
        const T GetSeperationWeight() const { return separationWeight; }
        void SetSeperationWeight(T val) { separationWeight = val; }
        const T GetSpeed() const { return boidSpeed; }
        void SetSpeed(T val) { boidSpeed = val; }
        const T GetViewDistance() const { return viewDistance; }
        void SetViewDistance(T val) {
            if (val < 0) throw std::runtime_error("View distance cannot be < 0");
            viewDistance = val;
        }
        const T GetGridSize() const { return gridSize; }
        void SetGridSize(T val, T max) {
            if (max / val > 1024.0) {
                val = max / 1024;
            }
            gridSize = val;
        }

    private:
        T alignmentWeight;
        T cohesionWeight;
        T separationWeight;
        T viewDistance;
        T boidSpeed;
        T areaSize;
        T gridSize;
        std::vector<Boid<T>*> boids_;
        std::map<int, std::vector<Boid<T>*>> boidsHash_;

        //T borderWeight
        T viewAngle;
        //std::list<Behavior<T>> behaviors;
};
