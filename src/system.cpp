#include "system.h"

System::System():
    m_integrator(new Integrator(this)),
    m_nTimeSteps(0)
{
    uint nUnitCells = 3;
    double unitCellLength = 1.5;

    double systemLength = nUnitCells*unitCellLength;
    m_systemSize = Vector3D(systemLength, systemLength, systemLength);
    m_halfSystemSize = m_systemSize/2.0;

    double temperature = 1.05;
    SystemGenerator generator;
    m_atom_objects = generator.generateFCC(nUnitCells, unitCellLength);
    for (Atom& atom : m_atom_objects)
    {
        m_atoms.push_back(&atom);
        m_constAtoms.push_back(&atom); // casts to const?
    }
    generator.boltzmannDistributeVelocities(temperature, m_atoms);
}

//System::System(std::vector<Atom *> atoms, Vector3D systemSize):
//    m_atoms(atoms),
//    m_integrator(new Integrator(this)),
//    m_systemSize(systemSize),
//    m_halfSystemSize(systemSize/2.0)
//{
//}

const std::vector<Atom *> &System::getMutableAtoms() const
{
    return m_atoms;
}

const std::vector<const Atom *> &System::getAtoms() const
{
    return m_constAtoms;
}

Atom *System::getMutableAtom(const uint i) const
{
    return m_atoms[i];
}

const Atom *System::getAtom(const uint i) const
{
//    return const_cast<const Atom*>(m_atoms[i]);
//    return m_atoms[i]; // automatic cast to const?
    return m_constAtoms[i]; // better ?
}

const Vector3D &System::getSystemSize() const
{
    return m_systemSize;
}

const Vector3D &System::getHalfSystemSize() const
{
    return m_halfSystemSize;
}

void System::doOneTimeStep(const double dt)
{
    m_integrator->integrate(dt);
    m_nTimeSteps++;
}

void System::writeToXYZ(const std::string& filename)
{
    std::ofstream ofile(filename);

    // Header
    ofile << nAtoms() << std::endl;
    ofile << "Comment" << std::endl;

    // Atoms
    for (Atom* atom : m_atoms) {
        ofile << atom->getIndex() << " ";
        for (uint i = 0; i < 3; i++) {
            ofile << atom->getPosition()[i] << " ";
        }
        for (uint i = 0; i < 3; i++) {
            ofile << atom->getVelocity()[i] << " ";
        }
        for (uint i = 0; i < 3; i++) {
            ofile << atom->getForce()[i] << " ";
        }
        ofile << atom->getVelocity().length() << " ";
        ofile << std::endl;
    }
}

uint System::nAtoms() const
{
    return m_atoms.size();
}
