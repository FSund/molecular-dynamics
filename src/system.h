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
//    System(std::vector<Atom *> atoms, Vector3D systemSize);

    const std::vector<Atom*> &getMutableAtoms() const;
    const std::vector<const Atom*> &getAtoms() const;
    Atom *getMutableAtom(const uint i) const;
    const Atom *getAtom(const uint i) const;
    const Vector3D &getSystemSize() const;
    const Vector3D &getHalfSystemSize() const;

    void doOneTimeStep(const double dt);
    void writeToXYZ(const std::string& filename);
    void writeToXYZWithBoxID(const std::string& filename);
    uint nAtoms() const;

private:
    std::vector<Atom *> m_atoms;
    std::vector<const Atom *> m_constAtoms;
    std::vector<Atom> m_atom_objects;
    Integrator *m_integrator;

//    std::vector<Box> m_boxes;
    uint m_nTimeSteps;

    Vector3D m_systemSize;
    Vector3D m_halfSystemSize;
};

#endif // SYSTEM_H
