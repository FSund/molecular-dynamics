#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include <atom.h>
#include <integrator.h>
#include <systemgenerator.h>
#include <neighborlist.h>

// forward declarations
class Integrator;

class System
{
public:
    System() = delete;
    System(const uint nUnitCells, const double unitCellLength, const double forceCutoff);
//    System(std::vector<Atom*> atoms, Vector3D systemSize);

    inline const std::vector<Atom*> &getMutableAtoms() const;
    inline const std::vector<const Atom*> &getAtoms() const;
    inline Atom *getMutableAtom(const uint i) const;
    inline const Atom *getAtom(const uint i) const;
    inline const Vector3D &getSystemSize() const;
    inline const Vector3D &getHalfSystemSize() const;

    void doOneTimeStep(const double dt);
    void writeToXYZ(const std::string& filename);
    void writeToXYZWithBoxID(const std::string& filename);
    inline uint nAtoms() const;

private:
    std::vector<Atom*> m_atoms;
    std::vector<const Atom*> m_constAtoms;
    std::vector<Atom> m_atom_objects;
    Integrator *m_integrator;

    uint m_nTimeSteps;

    Vector3D m_systemSize;
    Vector3D m_halfSystemSize;
};

inline const std::vector<Atom*> &System::getMutableAtoms() const
{
    return m_atoms;
}

inline const std::vector<const Atom*> &System::getAtoms() const
{
    return m_constAtoms;
}

inline Atom *System::getMutableAtom(const uint i) const
{
    return m_atoms[i];
}

inline const Atom *System::getAtom(const uint i) const
{
//    return const_cast<const Atom*>(m_atoms[i]);
//    return m_atoms[i]; // automatic cast to const?
    return m_constAtoms[i]; // better ?
}

inline const Vector3D &System::getSystemSize() const
{
    return m_systemSize;
}

inline const Vector3D &System::getHalfSystemSize() const
{
    return m_halfSystemSize;
}

inline uint System::nAtoms() const
{
    return m_atoms.size();
}

#endif // SYSTEM_H
