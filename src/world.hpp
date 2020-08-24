#pragma once
#include <list>
#include <vector>
#include <map>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <thread>

#include "boid.hpp"
#include "behavior.hpp"
#include "combinedbehavior.hpp"
#include "avoidbordersbehavior.hpp"
#include "perftimer.hpp"

template <typename T>
class World {
public:
    World(T _alignmentWeight, T _cohesionWeight, T _separationWeight, T _viewDistance, T _boidSpeed, T _viewAngle, T _areaSize, int _numberOfBoids)
        : flockingBehavior(CombinedBehavior<T>(_alignmentWeight, _cohesionWeight, _separationWeight)), viewDistance(_viewDistance), boidSpeed(_boidSpeed), viewAngle(_viewAngle), areaSize(_areaSize) {
        initBoids(_numberOfBoids);
        SetGridSize(_viewDistance, _areaSize);
    }
    ~World() {
        for (auto boid : boids_) {
            delete boid;
        }
    }

    void AddBoid(Boid<T>* b) {
        boids_.push_back(b);
        int hash = b->CalculateHash(gridSize);
        b->SetCurrentHash(hash, (int) (areaSize / gridSize));
        newBoids_++;
    }
    void AddRandomBoids(std::mt19937 rng, std::uniform_real_distribution<T> vel_dist, std::uniform_real_distribution<T> pos_dist, int nr) {
        for (auto i = 0; i < nr; i++) {
            vector3d<T> speedV(vel_dist(rng), vel_dist(rng), vel_dist(rng)),
                        posV(pos_dist(rng), pos_dist(rng), pos_dist(rng));
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
    const int GetNumberOfBoids() const {
        return (int) boids_.size();
    }
    const std::vector<Boid<T>*> &GetBoids() const {
        return boids_;
    }
    void moveBoids() {
        static float speedfactor = 1.0;
        static double simulateMax = 0.0;
        static double collectMax = 0.0;

        PerfTimer perfTimer;
        if (newBoids_ != GetNumberOfBoids()) {
            UpdateBoids();
            newBoids_ = GetNumberOfBoids();
        }

        std::vector<std::thread> threads;

        int nr = 50, start = 0, end = nr;
        while (end < boids_.size()) {
            threads.push_back(std::thread(&World<T>::SimulateBoids, this, start, end, speedfactor));
            start = start + nr;
            end = end + nr;
        }
        if (start < boids_.size()) {
            threads.push_back(std::thread(&World<T>::SimulateBoids, this, start, (int) boids_.size(), speedfactor));
        }
        for (auto& t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

        double simulate = perfTimer.GetMS();
        if (simulate > simulateMax) {
            simulateMax = simulate;
            //std::cout << "Simulate: " << simulate << " ms" << std::endl;
        }

        int oldHash, newHash;
        for (auto boid :  boids_) {
            boid->SetNextToCurrent();
            oldHash = boid->GetCurrentHash();
            newHash = boid->CalculateHash(gridSize);
            if (newHash != oldHash) {
                boidsHash_[oldHash].erase(std::remove(boidsHash_[oldHash].begin(), boidsHash_[oldHash].end(), boid), boidsHash_[oldHash].end());
                if (boidsHash_.count(newHash) == 0) {
                    std::vector<Boid<T>*> blist;
                    boidsHash_.emplace(newHash, blist);
                }
                boidsHash_[newHash].push_back(boid);
                boid->SetCurrentHash(newHash, (int) (areaSize / gridSize));
            }
        }
        double total = perfTimer.GetMS();
        double collect = total - simulate;
        if (collect > collectMax) {
            collectMax = collect;
            //std::cout << "Collect: " << collect << " ms" << std::endl;
        }
        if (total > 16.67) {
            speedfactor = (T) (total / 16.67);
        }
        else {
            speedfactor = 1.0;
        }
    }

    void SimulateBoids(int start, int end, float speedfactor) {
        vector3d<T> velocity;

        for (auto it = boids_.begin() + start; it != boids_.begin() + end; it++)
        {
            velocity = borderBehavior.compute(boidsHash_, *it, viewDistance, areaSize) * boidSpeed * 0.02 * 2 * speedfactor / viewDistance;
            if (velocity.isZero()) {
                velocity = (*it)->GetVelocity();
                velocity += flockingBehavior.compute(boidsHash_, *it, viewDistance, viewAngle);
            } else {
                velocity += (*it)->GetVelocity();
            }
            if (!velocity.isZero()) {
                velocity.normalize();
            }
            (*it)->SetNextVelAndPos(velocity * boidSpeed * 0.02 * speedfactor, areaSize);
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
            std::uniform_real_distribution<T> vel_dist(-1, 1);
            std::uniform_real_distribution<T> pos_dist(viewDistance, areaSize-viewDistance);
            AddRandomBoids(rng, vel_dist, pos_dist, diff);
        }
    }

    // Property getters and setters
    const T GetAligmentWeight() const { return flockingBehavior.GetAligmentWeight(); }
    void SetAligmentWeight(T val) { flockingBehavior.SetAligmentWeight(val); }
    const T GetCohesionWeight() const { return flockingBehavior.GetCohesionWeight(); }
    void SetCohesionWeight(T val) { flockingBehavior.SetCohesionWeight(val); }
    const T GetSeperationWeight() const { return flockingBehavior.GetSeperationWeight(); }
    void SetSeperationWeight(T val) { flockingBehavior.SetSeperationWeight(val); }
    const T GetSpeed() const { return boidSpeed; }
    void SetSpeed(T val) { boidSpeed = val; }
    const T GetWorldSize() const { return areaSize; }
    void SetWorldSize(T val) {
        if (val < viewDistance) throw std::runtime_error("World size cannot be < view distance");
        areaSize = val;
        SetGridSize(viewDistance, areaSize);
    }
    const T GetViewDistance() const { return viewDistance; }
    void SetViewDistance(T val) {
        if (val < 0) throw std::runtime_error("View distance cannot be < 0");
        viewDistance = val;
        SetGridSize(viewDistance, areaSize);
    }
    const T GetViewAngle() const { return viewAngle; }
    void SetViewAngle(T val) { viewAngle = val; }
    const T GetGridSize() const { return gridSize; }
    void SetGridSize(T val, T max) {
        if (max / val > 1023.0) {
            val = max / 1023;
        }
        gridSize = val;
    }

private:
    T viewDistance;
    T boidSpeed;
    T areaSize;
    T gridSize;
    T viewAngle;
    std::vector<Boid<T>*> boids_;
    int newBoids_ = 0;
    std::map<int, std::vector<Boid<T>*>> boidsHash_;

    CombinedBehavior<T> flockingBehavior;
    AvoidBordersBehavior<T> borderBehavior;

    //uniform_real_distribution defined on float, double and long double. If others types are needed templates partial specialization is needed.
    void initBoids(int numberOfBoids) {
        std::random_device random_device;
        std::mt19937 rng(random_device());
        std::uniform_real_distribution<T> vel_dist(-1, 1);
        std::uniform_real_distribution<T> pos_dist(viewDistance, areaSize-viewDistance);
        AddRandomBoids(rng, vel_dist, pos_dist, numberOfBoids);
    }
};
