#ifndef FORCE_H
#define FORCE_H

#include <vector3d.h>

#include <atom.h>

class Force
{
public:
    Force() = delete; // Delete default constructur
    Force(const Vector3D systemSize);

    void calculateForceWithoutDisplacementVector(
            Atom *atom1,
            Atom *atom2);

    void calculateForceWithDisplacementVector(
            Atom *atom1,
            Atom *atom2,
            const Vector3D& displacementVector);

    inline void calculateForceUsingMinimumImageConvention(
            Atom *atom1,
            Atom *atom2);

    void calculateForceUsingMinimumImageConvention(Atom* atom1,
            Atom *atom2,
            const Vector3D& systemSize,
            const Vector3D& halfSystemSize);

private:
    inline Vector3D& calculateForce(const Vector3D& drVec);
    inline void calculateAndApplyForce(Atom *atom1, Atom *atom2, const Vector3D& drVec);

    Vector3D force;
    Vector3D drVec;
    double dr2;
    double dr6;
    double LJforce;

    Vector3D m_systemSize;
    Vector3D m_halfSystemSize;
};

inline void Force::calculateForceUsingMinimumImageConvention(Atom *atom1, Atom *atom2)
{
    calculateForceUsingMinimumImageConvention(atom1, atom2, m_systemSize, m_halfSystemSize);
}

inline void Force::calculateAndApplyForce(Atom *atom1, Atom *atom2, const Vector3D& drVec)
{
    calculateForce(drVec);

    atom1->addForce(force);
    atom2->addForce(-force);
}

inline Vector3D& Force::calculateForce(const Vector3D& drVec)
{
    dr2 = drVec[0]*drVec[0] + drVec[1]*drVec[1] + drVec[2]*drVec[2];
    dr6 = dr2*dr2*dr2;

    LJforce = 24.0*(2.0 - dr6)/(dr6*dr6*dr2);
    force = drVec*LJforce;

    return force;
}

#endif // FORCE_H
