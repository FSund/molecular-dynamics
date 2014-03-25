#ifndef FORCE_H
#define FORCE_H

#include <vector3d.h>

#include <atom.h>

class Force
{
public:
//    Force();
    void calculateForces(Atom *mainAtom, Atom *neighborAtom, const Vector3D& systemSize, const Vector3D& halfSystemSize);

private:
    Vector3D force;
    Vector3D drVec;
    double dr2;
    double dr6;
    double LJforce;
};

#endif // FORCE_H
