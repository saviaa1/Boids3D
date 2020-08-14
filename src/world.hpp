#pragma once
#include <list>
#include <vector>
#include <map>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <chrono>

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
            AddRandomBoids(rng, zeroToSize, numberOfBoids);
        }
        void AddBoid(Boid<T>* b) {
            boids_.push_back(b);
            newBoids_++;
        }
        void AddRandomBoids(std::mt19937 rng, std::uniform_real_distribution<T> dist, int nr) {
            for (auto i = 0; i < nr; i++) {
                vector3d<T> speedV(dist(rng), dist(rng), dist(rng)),
                            posV(dist(rng), dist(rng), dist(rng));
                //std::cout << speedV << posV << "..\n";
                if (!speedV.isZero()) {
                    speedV.normalize();
                }
                Boid<T>* b = new Boid<T>(speedV, posV);
                AddBoid(b);
            }
        }
        void SetNewNumberOfBoids(int nr) {
            newBoids_ = nr;
        }
        const size_t GetNumberOfBoids() const {
            return boids_.size();
        }
        const std::vector<Boid<T>*> &GetBoids() const {
            return boids_;
        }
        void moveBoids() {
            static auto max1 = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
            static auto max2 = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
            static bool max2set = false;
            static float speedfactor = 1.0;

            auto start = std::chrono::high_resolution_clock::now();
            //TODO: chainge behaviours to use behaviours list.
            SeparationBehavior<T> sep;
            CohesionBehavior<T> coh;
            AlignmentBehavior<T> ali;
            vector3d<T> velocity;
            if (newBoids_ != GetNumberOfBoids()) {
                UpdateBoids();
                newBoids_ = GetNumberOfBoids();
            }

            for (auto boid : boids_) {
                std::vector<int> hashesToCheck = boid->hashesToCheck();
                std::vector<Boid<T>*> temp;
                for( auto hash : hashesToCheck )
                {
                    for( auto hashBoid : boidsHash_[hash] )
                    {
                        temp.push_back(hashBoid);
                    }
                }
                velocity = (sep.compute(temp, boid, viewDistance, viewAngle) * separationWeight)
                    + (coh.compute(temp, boid, viewDistance, viewAngle) * cohesionWeight)
                    + (ali.compute(temp, boid, viewDistance, viewAngle) * alignmentWeight);
                if (!velocity.isZero()) { velocity.normalize(); }
                boid->SetNextVelAndPos(velocity * boidSpeed * speedfactor, areaSize);
            }
            auto middle = std::chrono::high_resolution_clock::now();
            if (middle - start > max1) {
                max1 = middle - start;
                std::cout << "max1: " << std::chrono::duration_cast<std::chrono::milliseconds>(max1).count() << std::endl;
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
                        std::vector<Boid<T>*> blist;
                        boidsHash_.emplace(newHash, blist);
                    }
                    boidsHash_[newHash].push_back(boid);
                    boid->SetCurrentHash(newHash);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            if (end - middle > max2) {
                if (max2set) {
                    max2 = end - middle;
                }
                max2set = true;
                std::cout << "max2: " << std::chrono::duration_cast<std::chrono::milliseconds>(max2).count() << std::endl;
            }
            auto total = end - start;
            if (std::chrono::duration_cast<std::chrono::milliseconds>(total).count() > 17) {
                speedfactor = std::chrono::duration_cast<std::chrono::milliseconds>(total).count() / 17;
            }
        }
        void UpdateBoids() {
            int diff = newBoids_ - GetNumberOfBoids();
            int oldHash;
            while  (diff < 0) {
                Boid<T>* boid = boids_.back();
                oldHash = boid->GetCurrentHash();
                boidsHash_[oldHash].erase(std::remove(boidsHash_[oldHash].begin(), boidsHash_[oldHash].end(), boid), boidsHash_[oldHash].end());
                boids_.pop_back();
                diff++;
            }
            if (diff > 0) {
                std::random_device random_device;
                std::mt19937 rng(random_device());
                std::uniform_real_distribution<T> zeroToSize(0, areaSize);
                AddRandomBoids(rng, zeroToSize, diff);
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
        const T GetViewAngle() const { return viewAngle; }
        void SetViewAngle(T val) { viewAngle = val; }
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
        T viewAngle;
        std::vector<Boid<T>*> boids_;
        int newBoids_ = 0;
        std::map<int, std::vector<Boid<T>*>> boidsHash_;

        //T borderWeight
        //std::list<Behavior<T>> behaviors;
};
