#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <vector>
#include <cmath>

#include <vector3d.h>

#include <force.h>
#include <system.h>
#include <neighborlist.h>
#include <linearindexfunctions.h>

// forward declaration
class Force;
class System;
class NeighborList;

class Integrator
{
public:
    Integrator() = delete; // delete default constructor
    Integrator(System *system, const double forceCutoff);

    void integrate(const double dt);
    const std::vector<NeighborList> getNeighborLists() const;

private:
    void calculateForces();
    void calculateForcesUsingBoxes();

    System *m_system;
    Force *m_force;
    std::vector<NeighborList> m_neighborLists;

    bool m_useBoxes = true;
};

#endif // INTEGRATOR_H
