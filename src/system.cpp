#include "system.h"

System::System(const uint nUnitCells, const double unitCellLength, const double forceCutoff):
    m_nTimeSteps(0)
{
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

    m_integrator = new Integrator(this, forceCutoff);
}

//System::System(std::vector<Atom*> atoms, Vector3D systemSize):
//    m_atoms(atoms),
//    m_integrator(new Integrator(this)),
//    m_systemSize(systemSize),
//    m_halfSystemSize(systemSize/2.0)
//{
//}

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
    for (Atom *atom : m_atoms) {
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
        ofile << atom->getForce().length() << " ";
        ofile << std::endl;
    }
}

void System::writeToXYZWithBoxID(const std::string& filename)
{
    std::ofstream ofile(filename);
    if (!ofile.is_open())
    {
        std::cout << "Error: Couldn't open file \"" << filename << "\" for writing." << std::endl;
    }
    else
    {
        // Header
        ofile << nAtoms() << std::endl;
        ofile << "Comment" << std::endl;

        // Atoms
        for (const NeighborList &list : m_integrator->getNeighborLists())
        {
            for (const Atom *atom : list.getAtoms())
            {
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
                ofile << atom->getForce().length() << " ";
                ofile << list.getLinearIndex() << " ";
                ofile << std::endl;
            }
        }
    }
}
