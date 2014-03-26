#include <integrator.h>

Integrator::Integrator(System *system, const double forceCutoff):
    m_system(system),
    m_force(new Force(system->getSystemSize()))
{
    // set up neighborlists
    std::vector<int> nLists = {
        int(std::floor(m_system->getSystemSize()[0] / forceCutoff)), // int() to avoid narrowing warning...
        int(std::floor(m_system->getSystemSize()[1] / forceCutoff)),
        int(std::floor(m_system->getSystemSize()[2] / forceCutoff))
    };

    Vector3D boxSize(
        system->getSystemSize()[0]/double(nLists[0]),
        system->getSystemSize()[1]/double(nLists[1]),
        system->getSystemSize()[2]/double(nLists[2])
    );

    NeighborList::m_boxSize = boxSize;

    // Sorting atoms into neighborlists
    std::vector<std::vector<Atom *> > neighborListAtoms(nLists[0]*nLists[1]*nLists[2]);
    for (Atom *atom : m_system->getMutableAtoms())
    {
        std::vector<int> index = {
            int(std::floor(atom->getPosition()[0] / boxSize[0])),
            int(std::floor(atom->getPosition()[1] / boxSize[1])),
            int(std::floor(atom->getPosition()[2] / boxSize[2]))
        };
        int linearIndex = convert3dIndicesToLinearIndex(index, nLists);
        neighborListAtoms[linearIndex].push_back(atom);
    }

    // Creating neighborlist objects/vector
    for (int i = 0; i < nLists[0]; i++)
    {
        for (int j = 0; j < nLists[1]; j++)
        {
            for (int k = 0; k < nLists[2]; k++)
            {
                Vector3D origin = Vector3D(i, j, k)*boxSize;

                int linearIndex = convert3dIndicesToLinearIndex(i, j, k, nLists);
                m_neighborLists.push_back(
                    NeighborList(origin, neighborListAtoms[linearIndex], std::vector<int>{i, j, k}, linearIndex)
                );
            }
        }
    }

    for (NeighborList &list : m_neighborLists)
    {
        list.findNeighbors(m_neighborLists, nLists, m_system->getSystemSize());
    }
}

void Integrator::integrate(const double dt)
{
    for (Atom *atom : m_system->getMutableAtoms()) {
        atom->m_velocity += atom->getForce()*dt/2.0;
        atom->m_position += atom->getVelocity()*dt;

        // periodic boundary conditions
        for (uint i = 0; i < 3; i++) {
            if      (atom->getPosition()[i] < 0.0)                           atom->m_position[i] += m_system->getSystemSize()[i];
            else if (atom->getPosition()[i] >= m_system->getSystemSize()[i]) atom->m_position[i] -= m_system->getSystemSize()[i];
        }
    }

    if (m_useBoxes)
    {
        // Remove atoms that went outside box from lists
        std::list<Atom *> atomsOutsideBox;
        for (NeighborList &list : m_neighborLists)
        {
            list.purgeAtoms(atomsOutsideBox);
        }

        // Put atoms that went outside box in correct box
        for (NeighborList &list : m_neighborLists)
        {
            list.findMyAtomsInList(atomsOutsideBox);
        }

        calculateForcesUsingBoxes();
    }
    else
    {
        calculateForces();
    }

    for (Atom *atom : m_system->getMutableAtoms()) {
        atom->m_velocity += atom->getForce()*dt/2.0;
    }
}

void Integrator::calculateForces()
{
    for (Atom *atom : m_system->getMutableAtoms())
    {
        atom->setForce(Vector3D(0.0, 0.0, 0.0));
    }
    for (uint mainAtomIndex = 0; mainAtomIndex < m_system->nAtoms(); mainAtomIndex++) // this is bad, should use iterators or C++11 range-based for
    {
        for (uint neighborAtomIndex = mainAtomIndex+1; neighborAtomIndex < m_system->nAtoms(); neighborAtomIndex++) // this is bad, should use iterators or C++11 range-based for
        {
            m_force->calculateForceUsingMinimumImageConvention(
                        m_system->getMutableAtom(mainAtomIndex),
                        m_system->getMutableAtom(neighborAtomIndex),
                        m_system->getSystemSize(),
                        m_system->getHalfSystemSize());
        }
    }
}

void Integrator::calculateForcesUsingBoxes()
{
    for (Atom *atom : m_system->getMutableAtoms())
    {
        atom->setForce(Vector3D(0.0, 0.0, 0.0));
    }
    for (NeighborList &list : m_neighborLists)
    {
        list.calculateForces(m_force);
    }
}
