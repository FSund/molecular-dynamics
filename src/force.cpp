#include <force.h>

Force::Force(const Vector3D systemSize):
    m_systemSize(systemSize),
    m_halfSystemSize(systemSize/2.0)
{

}

void Force::calculateForces(Atom *mainAtom, Atom *neighborAtom)
{
    calculateForces(mainAtom, neighborAtom, m_systemSize, m_halfSystemSize);
}

void Force::calculateForces(Atom *mainAtom, Atom *neighborAtom, const Vector3D &systemSize, const Vector3D &halfSystemSize)
{
    drVec = mainAtom->getPosition() - neighborAtom->getPosition();

    // Minimum image convention
    // TODO: Get rid of this, use displacementvectors instead
    for (uint i = 0; i < 3; i++) {
        if      (drVec[i] >  halfSystemSize[i]) drVec[i] -= systemSize[i];
        else if (drVec[i] < -halfSystemSize[i]) drVec[i] += systemSize[i];
    }

    dr2 = drVec[0]*drVec[0] + drVec[1]*drVec[1] + drVec[2]*drVec[2];
    dr6 = dr2*dr2*dr2;

    LJforce = 24.0*(2.0 - dr6)/(dr6*dr6*dr2);
    force = drVec*LJforce;

    mainAtom->addForce(force);
    neighborAtom->addForce(-force);
}
