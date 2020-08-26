#pragma once
#include <list>
#include <vector>
#define USEMAP 0
#if USEMAP
#include <map>
#define USEDMAP std::map
#else
#include <unordered_map>
#define USEDMAP std::unordered_map
#endif
#include <stdexcept>
#include <random>
#include <algorithm>
#include <thread>

#include "boid.hpp"
#include "behavior.hpp"
#include "combinedbehavior.hpp"
#include "avoidbordersbehavior.hpp"
#include "predatorbehavior.hpp"
#include "perftimer.hpp"

template <typename T>
class World {
public:
    World(T _alignmentWeight, T _cohesionWeight, T _separationWeight, T _viewDistance, T _boidSpeed, T _viewAngle, T _areaSize, int _numberOfBoids)
        : flockingBehavior(CombinedBehavior<T>(_alignmentWeight, _cohesionWeight, _separationWeight)), viewDistance(_viewDistance), boidSpeed(_boidSpeed), viewAngle(_viewAngle), areaSize(_areaSize) {
        initBoids(_numberOfBoids);
        SetGridSize(_viewDistance, _areaSize);
        //Set nullptr if predator off at startup, else for expamle boids_.front();
        predator = nullptr;// boids_.front();
        AvoidPredatorBeh = AvoidPredatorBehavior<T>();
        PursueBoidsBeh = PursueBoidsBehavior<T>();
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
        static float speedfactor = 1.0f;
        static double simulateMax = 0.0;
        static double collectMax = 0.0;

        PerfTimer perfTimer;
        if (newBoids_ != GetNumberOfBoids()) {
            UpdateBoids();
            newBoids_ = GetNumberOfBoids();
        }

        std::vector<std::thread> threads;

        int nr = 100, start = 0, end = nr;
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
        tick++;
    }

    void SimulateBoids(int start, int end, float speedfactor) {
        vector3d<T> velocity;

        for (auto it = boids_.begin() + start; it != boids_.begin() + end; it++)
        {
            velocity = borderBehavior.compute(boidsHash_, *it, viewDistance, areaSize, 0, tick) * boidSpeed * 0.02 * 2 * speedfactor / viewDistance;
            if (velocity.isZero()) {
                //if predator pursue closest boid. Will be calculated if predator pointer defined, if pointer is nullptr no predator or avoidPredator behavior.
                if (predator && *it == predator) {
                    velocity = (*it)->GetVelocity();
                    velocity += PursueBoidsBeh.compute(boidsHash_, *it, viewDistance, 0, boidSpeed, tick);
                }
                //else normal behavior + avoid predator if in viewDistance.
                else {
                    velocity = (*it)->GetVelocity();
                    velocity += flockingBehavior.compute(boidsHash_, *it, viewDistance, viewAngle, boidSpeed, tick);
                    if (predator) { velocity += AvoidPredatorBeh.computeA(predator, *it, areaSize, 0); }
                }
            } else {
                velocity += (*it)->GetVelocity();
            }
            if (!velocity.isZero()) {
                velocity.normalize();
            }
            if (predator && *it == predator) {
                (*it)->SetNextVelAndPos(velocity * boidSpeed * (T) 0.02 * speedfactor * predSpeedFactor, areaSize);
            } else {
                (*it)->SetNextVelAndPos(velocity * boidSpeed * (T) 0.02 * speedfactor, areaSize);
            }
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
    const T GetSeparationWeight() const { return flockingBehavior.GetSeparationWeight(); }
    void SetSeparationWeight(T val) { flockingBehavior.SetSeparationWeight(val); }
    const T GetSpeed() const { return boidSpeed; }
    void SetSpeed(T val) { boidSpeed = val; }
    const T GetWorldSize() const { return areaSize; }
    void SetWorldSize(T val) {
        if (val != areaSize) {
            if (val < viewDistance) throw std::runtime_error("World size cannot be < view distance");
            areaSize = val;
            SetGridSize(viewDistance, areaSize);
            SetWorldSizeChanged(true);
        }
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
    const Boid<T>* GetPredator() const { return predator; }
    void SetPredator(bool val) { 
        if (val) { 
            predator = boids_[0];
        } else {
            predator = nullptr;
        }
    }

    //randRand is the default and active on startup
    //change randMov on and of and return bool value of the status.
    bool SwitchRandMov() {
        bool val = true;
        if (flockingBehavior.getRandStatus()) { val = false; }
        flockingBehavior.setRandStatus(val);
        PursueBoidsBeh.setRandStatus(val);
        return val;
    } 
    const bool GetWorldSizeChanged() const { return size_changed_; }
    void SetWorldSizeChanged(bool val) {
        size_changed_ = val;
    }

private:
    T viewDistance;
    T boidSpeed;
    T predSpeedFactor = 0.9f;
    T areaSize;
    T gridSize;
    T viewAngle;
    int newBoids_ = 0;
    Boid<T>* predator;
    std::vector<Boid<T>*> boids_;
    USEDMAP<int, std::vector<Boid<T>*>> boidsHash_;
    bool size_changed_ = false;
    CombinedBehavior<T> flockingBehavior;
    AvoidBordersBehavior<T> borderBehavior;
    AvoidPredatorBehavior<T> AvoidPredatorBeh;
    PursueBoidsBehavior<T> PursueBoidsBeh;

    int tick = 0;

    //uniform_real_distribution defined on float, double and long double. If others types are needed templates partial specialization is needed.
    void initBoids(int numberOfBoids) {
        std::random_device random_device;
        std::mt19937 rng(random_device());
        std::uniform_real_distribution<T> vel_dist(-1, 1);
        std::uniform_real_distribution<T> pos_dist(viewDistance, areaSize-viewDistance);
        AddRandomBoids(rng, vel_dist, pos_dist, numberOfBoids);
    }
};
