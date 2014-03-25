#ifndef ATOM_H
#define ATOM_H

#include <vector3d.h>

class Integrator;

class Atom
{
public:
    friend class Integrator;

    Atom();
    Atom(
        const Vector3D& position,
        const Vector3D& velocity = Vector3D(0.0, 0.0, 0.0),
        const Vector3D& force    = Vector3D(0.0, 0.0, 0.0)
    );

    inline const Vector3D& getPosition() const;
    inline const Vector3D& getVelocity() const;
    inline const Vector3D& getForce() const;
    inline int getIndex() const;

    inline void setPosition(const Vector3D& position);
    inline void setVelocity(const Vector3D& velocity);
    inline void setForce(const Vector3D& force);

    inline void addForce(const Vector3D& force);

private:
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_force;

    static int m_nAtoms;
    int m_atomIndex;
};

const Vector3D& Atom::getPosition() const { return m_position; }
const Vector3D& Atom::getVelocity() const { return m_velocity; }
const Vector3D& Atom::getForce() const { return m_force; }

int Atom::getIndex() const { return m_atomIndex; }

void Atom::setPosition(const Vector3D& position) { m_position = position; }
void Atom::setVelocity(const Vector3D& velocity) { m_velocity = velocity; }
void Atom::setForce(const Vector3D& force) { m_force = force; }

inline void Atom::addForce(const Vector3D& force) { m_force += force; }

#endif // ATOM_H
