#ifndef NEIGHBORLIST_H
#define NEIGHBORLIST_H

#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

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
    NeighborList(const Vector3D& origin, const std::vector<Atom*> &atoms, const std::vector<int>& index, const int linearIndex);

    void findNeighbors(std::vector<NeighborList>& lists, const std::vector<int> &nLists, const Vector3D& systemSize);
    void purgeAtoms(std::list<Atom*> &atomsOutsideBox);
    void findMyAtomsInList(std::list<Atom*> &atoms);

    void calculateForces(Force *force);

    inline const std::list<Atom*>& getAtoms() const;
    inline int getLinearIndex() const;

private:
    std::vector<NeighborList*> m_neighbors; // Would like to have this const, but that's hard to do, since we need to have created all list objects before making a list over all neighbors for each list.
    std::list<Atom*> m_atoms;
    Vector3D m_origin;
    std::vector<Vector3D> m_displacementVectors;
    std::vector<int> m_index;
    int m_linearIndex;

    static Vector3D m_boxSize;

    inline void calcuateForceFromBox(Atom *atom1, Force *force, const Vector3D& displacementVector);
    inline void calcuateForceFromSelf(const std::list<Atom*>::iterator& atom1, Force *force);
};

inline const std::list<Atom*>&NeighborList::getAtoms() const
{
    return m_atoms;
}

inline int NeighborList::getLinearIndex() const
{
    return m_linearIndex;
}

inline void NeighborList::calcuateForceFromSelf(const std::list<Atom*>::iterator &atom1, Force *force)
{
    for (auto atom2 = std::next(atom1); atom2 != m_atoms.end(); ++atom2) // std::next() gets iterator to next without incrementing
    {
        force->calculateForceWithoutDisplacementVector(*atom1, *atom2);
    }
}

inline void NeighborList::calcuateForceFromBox(Atom *atom1, Force *force, const Vector3D &displacementVector)
{
    for (Atom *atom2 : m_atoms)
    {
        force->calculateForceWithDisplacementVector(atom1, atom2, displacementVector);
    }
}

#endif // NEIGHBORLIST_H
