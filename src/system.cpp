#include "system.h"

System::System():
    m_integrator(new Integrator(this)),
    m_nTimeSteps(0)
{
//    m_integrator = new Integrator(*this);

//    uint nUnitCells = 3;
//    double unitCellLength = 1.5;

//    Vector3D position;
//    Vector3D velocity;
//    for (uint i = 0; i < nUnitCells; i++) {
//        for (uint j = 0; j < nUnitCells; j++) {
//            for (uint k = 0; k < nUnitCells; k++) {
//                double x = i*unitCellLength;
//                double y = j*unitCellLength;
//                double z = k*unitCellLength;

//                velocity = randVelocity();
//                position = Vector3D(x,                      y,                      z);
//                atoms.push_back(Atom(position, velocity));

//                velocity = randVelocity();
//                position = Vector3D(x,                      y + unitCellLength*0.5, z + unitCellLength*0.5);
//                atoms.push_back(Atom(position, velocity));

//                velocity = randVelocity();
//                position = Vector3D(x + unitCellLength*0.5, y + unitCellLength*0.5, z);
//                atoms.push_back(Atom(position, velocity));

//                velocity = randVelocity();
//                position = Vector3D(x + unitCellLength*0.5, y,                      z + unitCellLength*0.5);
//                atoms.push_back(Atom(position, velocity));
//            }
//        }
//    }

//    // remove drift
//    Vector3D meanVelocity;
//    for (const Atom& atom : atoms) {
//        meanVelocity += atom.getVelocity();
//    }
//    meanVelocity /= double(atoms.size());
//    for (Atom& atom : atoms) {
//        atom.m_velocity -= meanVelocity;
//    }

    Atom* atom1 = new Atom(Vector3D(5, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));
    m_atoms.push_back(atom1);
    Atom* atom2 = new Atom(Vector3D(10, 0.0, 0.0), Vector3D(-1.0, 0.0, 0.0));
    m_atoms.push_back(atom2);

    m_systemSize = Vector3D(15.0, 1.0, 1.0);
    m_halfSystemSize = m_systemSize/2.0;

    //    writeToXYZ("initial_state.xyz");
}

//System::System(std::vector<Atom *> atoms, Vector3D systemSize):
//    m_atoms(atoms),
//    m_integrator(new Integrator(this)),
//    m_systemSize(systemSize),
//    m_halfSystemSize(systemSize/2.0)
//{
//}

const std::vector<Atom *> System::atoms() const
{
    return m_atoms;
}

const Vector3D System::systemSize() const
{
    return m_systemSize;
}

const Vector3D System::halfSystemSize() const
{
    return m_halfSystemSize;
}

void System::doOneTimeStep(const double dt)
{
    for (Atom* atom : m_atoms) {
        atom->m_velocity += atom->getForce()*dt/2.0;
        atom->m_position += atom->getVelocity()*dt;

        // periodic boundary conditions
        for (uint i = 0; i < 3; i++) {
            if (atom->getPosition()[i] < 0.0) atom->m_position[i] += systemSize()[i];
            else if (atom->getPosition()[i] >= systemSize()[i]) atom->m_position[i] -= systemSize()[i];
        }
    }

    m_integrator->calculateForces();

    for (Atom* atom : m_atoms) {
        atom->m_velocity += atom->getForce()*dt/2.0;
    }

    m_nTimeSteps++;
}

Vector3D System::randVelocity()
{
    double factor = 1.0;
    return Vector3D(double(std::rand())/double(RAND_MAX)*2.0*factor - factor,
                    double(std::rand())/double(RAND_MAX)*2.0*factor - factor,
                    double(std::rand())/double(RAND_MAX)*2.0*factor - factor);
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
        ofile << std::endl;
    }
}

uint System::nAtoms() const
{
    return m_atoms.size();
}
