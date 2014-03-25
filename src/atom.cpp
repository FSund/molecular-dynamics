#include "atom.h"

int Atom::m_nAtoms = 0; // must be set in implementation file

Atom::Atom():
    m_position(Vector3D(0.0, 0.0, 0.0)),
    m_velocity(Vector3D(0.0, 0.0, 0.0)),
    m_force(Vector3D(0.0, 0.0, 0.0)),
    m_atomIndex(Atom::m_nAtoms++) // set atomIndex equal to nAtoms, then increase nAtoms
{
}

Atom::Atom(const Vector3D& position, const Vector3D& velocity, const Vector3D& force):
    m_position(position),
    m_velocity(velocity),
    m_force(force),
    m_atomIndex(Atom::m_nAtoms++) // set atomIndex equal to nAtoms, then increase nAtoms
{
}
