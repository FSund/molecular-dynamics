#include <force.h>

Force::Force(const Vector3D systemSize):
    m_systemSize(systemSize),
    m_halfSystemSize(systemSize/2.0)
{
}

void Force::calculateForces(Atom *atom1, Atom *atom2, const Vector3D &displacementVector)
{
    drVec = atom1->getPosition() - atom2->getPosition() + displacementVector;

    dr2 = drVec[0]*drVec[0] + drVec[1]*drVec[1] + drVec[2]*drVec[2];
    dr6 = dr2*dr2*dr2;

    LJforce = 24.0*(2.0 - dr6)/(dr6*dr6*dr2);
    force = drVec*LJforce;

    atom1->addForce(force);
    atom2->addForce(-force);
}

void Force::calculateForcesUsingMinimumImageConvention(Atom *atom1, Atom *atom2)
{
    calculateForcesUsingMinimumImageConvention(atom1, atom2, m_systemSize, m_halfSystemSize);
}

void Force::calculateForcesUsingMinimumImageConvention(Atom *atom1, Atom *atom2, const Vector3D &systemSize, const Vector3D &halfSystemSize)
{
    drVec = atom1->getPosition() - atom2->getPosition();

    // Minimum image convention
    for (uint i = 0; i < 3; i++) {
        if      (drVec[i] >  halfSystemSize[i]) drVec[i] -= systemSize[i];
        else if (drVec[i] < -halfSystemSize[i]) drVec[i] += systemSize[i];
    }

    dr2 = drVec[0]*drVec[0] + drVec[1]*drVec[1] + drVec[2]*drVec[2];
    dr6 = dr2*dr2*dr2;

    LJforce = 24.0*(2.0 - dr6)/(dr6*dr6*dr2);
    force = drVec*LJforce;

    atom1->addForce(force);
    atom2->addForce(-force);
}
