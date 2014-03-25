#include <force.h>

void Force::calculateAndApplyForces(Atom *mainAtom, Atom *neighborAtom, const Vector3D &systemSize, const Vector3D &halfSystemSize)
{
//    neighborAtom = system->atoms()[neighborAtomIndex];

    drVec = mainAtom->getPosition() - neighborAtom->getPosition();

    // PBC/minimum image convention
    for (uint i = 0; i < 3; i++) {
        if (drVec[i] > halfSystemSize[i]) drVec[i] -= systemSize[i];
        else if (drVec[i] < -halfSystemSize[i]) drVec[i] += systemSize[i];
    }
    dr2 = drVec[0]*drVec[0] + drVec[1]*drVec[1] + drVec[2]*drVec[2];
    dr6 = dr2*dr2*dr2;

    LJforce = 24.0*(2.0 - dr6)/(dr6*dr6*dr2);
    force = drVec*LJforce;

    mainAtom->addForce(force);
    neighborAtom->addForce(-force);
}
