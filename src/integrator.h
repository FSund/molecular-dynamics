#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <vector3d.h>

#include <force.h>
#include <system.h>

// forward declaration
class Force;
class System;

class Integrator
{
public:
    Integrator() = delete; // delete default constructor
    Integrator(System *system);

    void integrate(const double dt);
    void calculateForces();

private:
    System *system;
    Force *force;
};

#endif // INTEGRATOR_H
