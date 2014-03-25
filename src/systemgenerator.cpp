#include <systemgenerator.h>

std::vector<Atom> SystemGenerator::generateFCC(const int nUnitCells, const double unitCellLength)
{
    uint nAtoms = 4*nUnitCells*nUnitCells*nUnitCells;
    std::vector<Atom> atoms;
    atoms.reserve(nAtoms);

    Vector3D position;
    for (int i = 0; i < nUnitCells; i++) {
        for (int j = 0; j < nUnitCells; j++) {
            for (int k = 0; k < nUnitCells; k++) {
                double x = i*unitCellLength;
                double y = j*unitCellLength;
                double z = k*unitCellLength;

                position = Vector3D(x,                      y,                      z);
                atoms.push_back(Atom(position));

                position = Vector3D(x,                      y + unitCellLength*0.5, z + unitCellLength*0.5);
                atoms.push_back(Atom(position));

                position = Vector3D(x + unitCellLength*0.5, y + unitCellLength*0.5, z);
                atoms.push_back(Atom(position));

                position = Vector3D(x + unitCellLength*0.5, y,                      z + unitCellLength*0.5);
                atoms.push_back(Atom(position));
            }
        }
    }

    return atoms;
}

void SystemGenerator::boltzmannDistributeVelocities(const double temperature, const std::vector<Atom *> atoms)
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, std::sqrt(temperature));

    Vector3D velocity;
    for (Atom *atom : atoms)
    {
        velocity = Vector3D(distribution(generator), distribution(generator), distribution(generator));
        atom->setVelocity(velocity);
    }

    removeDriftInVelocity(atoms);
}

void SystemGenerator::uniformDistributeVelocities(const double uniformRange, const std::vector<Atom*> atoms)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-uniformRange/2.0, uniformRange/2.0);

    Vector3D velocity;
    for (Atom *atom : atoms)
    {
        velocity = Vector3D(distribution(generator), distribution(generator), distribution(generator));
        atom->setVelocity(velocity);
    }

    removeDriftInVelocity(atoms);
}

void SystemGenerator::removeDriftInVelocity(const std::vector<Atom*> atoms)
{
    Vector3D meanVelocity;
    for (const Atom *atom : atoms) {
        meanVelocity += atom->getVelocity();
    }
    meanVelocity /= double(atoms.size());
    for (Atom *atom : atoms) {
        atom->setVelocity(atom->getVelocity() - meanVelocity);
    }
}
