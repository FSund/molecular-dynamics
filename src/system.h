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

// forward declarations
class Integrator;

class System
{
public:
    System();
//    System(std::vector<Atom *> atoms, Vector3D systemSize);

    const std::vector<Atom*> getAtoms() const;
    const Vector3D getSystemSize() const;
    const Vector3D getHalfSystemSize() const;

    void doOneTimeStep(const double dt);
    void writeToXYZ(const std::string& filename);
    uint nAtoms() const;

private:
    std::vector<Atom *> m_atoms;
    std::vector<Atom> m_atom_objects;
    Integrator *m_integrator;

//    std::vector<Box> m_boxes;
    uint m_nTimeSteps;

    Vector3D m_systemSize;
    Vector3D m_halfSystemSize;
};

#endif // SYSTEM_H
