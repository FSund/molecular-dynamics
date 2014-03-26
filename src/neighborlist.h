#ifndef NEIGHBORLIST_H
#define NEIGHBORLIST_H

#include <list>
#include <vector>
#include <algorithm>

#include <vector3d.h>
#include <linearindexfunctions.h>

#include <atom.h>
#include <system.h>
#include <force.h>

// Forward declarations
class System;
class Atom;

class NeighborList
{
    friend class Integrator;

public:
    NeighborList() = delete; // Delete default constructor
    NeighborList(const Vector3D displacement, const std::vector<Atom *> &atoms, const std::vector<int> index, const int linearIndex);

    void findNeighbors(std::vector<NeighborList>& lists, const std::vector<int> &nLists);
    void calculateForces(Force* force);
    void purgeAtoms(std::list<Atom *> &atomsOutsideBox);
    void findMyAtomsInList(std::list<Atom *> &atoms);

    const std::list<Atom *>& getAtoms() const;
    int getLinearIndex() const;

private:
    std::vector<NeighborList *> m_neighbors; // Would like to have this const, but that's hard to do, since we need to have created all list objects before making a list over all neighbors for each list.
    std::list<Atom *> m_atoms;
    Vector3D m_displacement;
    std::vector<Vector3D> m_displacementVectors;
    std::vector<int> m_index;
    int m_linearIndex;

    static Vector3D m_boxSize;

    void calcuateForcesFromBox(Atom *atom1, Force *force);
        void calcuateForcesFromSelf(Atom *atom, Force *force);
};

#endif // NEIGHBORLIST_H
