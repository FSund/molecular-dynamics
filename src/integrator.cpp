#include <integrator.h>

Integrator::Integrator(System *system):
    system(system),
    force(new Force)
{
}

void Integrator::calculateForces()
{
    for (Atom* atom : system->atoms())
    {
        atom->setForce(Vector3D(0.0, 0.0, 0.0));
    }
    for (uint mainAtomIndex = 0; mainAtomIndex < system->nAtoms(); mainAtomIndex++) // this is bad, should use iterators or C++11 range-based for
    {
        for (uint neighborAtomIndex = mainAtomIndex+1; neighborAtomIndex < system->nAtoms(); neighborAtomIndex++) // this is bad, should use iterators or C++11 range-based for
        {
            force->calculateAndApplyForces(system->atoms()[mainAtomIndex], system->atoms()[neighborAtomIndex], system->systemSize(), system->halfSystemSize());
        }
    }
}
