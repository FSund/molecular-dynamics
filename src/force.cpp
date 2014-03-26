#include <force.h>

Force::Force(const Vector3D systemSize):
    m_systemSize(systemSize),
    m_halfSystemSize(systemSize/2.0)
{
}

void Force::calculateForceWithoutDisplacementVector(Atom *atom1, Atom *atom2)
{
    drVec = atom1->getPosition() - atom2->getPosition();

    calculateAndApplyForce(atom1, atom2, drVec);
}

void Force::calculateForceWithDisplacementVector(Atom *atom1, Atom *atom2, const Vector3D &displacementVector)
{
    drVec = atom1->getPosition() - atom2->getPosition() + displacementVector;

    calculateAndApplyForce(atom1, atom2, drVec);
}

void Force::calculateForceUsingMinimumImageConvention(Atom *atom1, Atom *atom2, const Vector3D &systemSize, const Vector3D &halfSystemSize)
{
    drVec = atom1->getPosition() - atom2->getPosition();

    // Minimum image convention
    for (uint i = 0; i < 3; i++) {
        if      (drVec[i] >  halfSystemSize[i]) drVec[i] -= systemSize[i];
        else if (drVec[i] < -halfSystemSize[i]) drVec[i] += systemSize[i];
    }

    calculateAndApplyForce(atom1, atom2, drVec);
}
