#include <integrator.h>

Integrator::Integrator(System *system):
    system(system),
    force(new Force)
{
}

void Integrator::integrate(const double dt)
{
    for (Atom *atom : system->getAtoms()) {
        atom->m_velocity += atom->getForce()*dt/2.0;
        atom->m_position += atom->getVelocity()*dt;

        // periodic boundary conditions
        for (uint i = 0; i < 3; i++) {
            if      (atom->getPosition()[i] < 0.0)                         atom->m_position[i] += system->getSystemSize()[i];
            else if (atom->getPosition()[i] >= system->getSystemSize()[i]) atom->m_position[i] -= system->getSystemSize()[i];
        }
    }

    calculateForces();

    for (Atom *atom : system->getAtoms()) {
        atom->m_velocity += atom->getForce()*dt/2.0;
    }
}

void Integrator::calculateForces()
{
    for (Atom *atom : system->getAtoms())
    {
        atom->setForce(Vector3D(0.0, 0.0, 0.0));
    }
    for (uint mainAtomIndex = 0; mainAtomIndex < system->nAtoms(); mainAtomIndex++) // this is bad, should use iterators or C++11 range-based for
    {
        for (uint neighborAtomIndex = mainAtomIndex+1; neighborAtomIndex < system->nAtoms(); neighborAtomIndex++) // this is bad, should use iterators or C++11 range-based for
        {
            force->calculateForces(
                        system->getAtoms()[mainAtomIndex],
                        system->getAtoms()[neighborAtomIndex],
                        system->getSystemSize(),
                        system->getHalfSystemSize());
        }
    }
}
