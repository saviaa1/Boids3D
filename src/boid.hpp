#pragma once

class Boid
{
public:
    Boid();
    ~Boid();

private:
    float mass;
    //vector3D position;
    int positionIndex;
    //vector3D nextPosition;
    int nextPositionIndex;
    //vector3D velocity;
    float maxForce;
    float maxSpeed;
    //vector3D orientation;
};