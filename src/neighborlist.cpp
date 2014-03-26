#include <neighborlist.h>

Vector3D NeighborList::m_boxSize;

NeighborList::NeighborList(
        const Vector3D displacement,
        const std::vector<Atom *> &atoms,
        const std::vector<int> index,
        const int linearIndex):
//    system(system),
    m_atoms(std::list<Atom *>(atoms.begin(), atoms.end())), // "Converting" std::vector to std::list
    m_displacement(displacement),
    m_index(index),
    m_linearIndex(linearIndex)
{
}

void NeighborList::findNeighbors(
        std::vector<NeighborList> &lists, // This can't be const because m_neighbors.push_back(&lists[linearIndex]) doesn't like it
        const std::vector<int> &nLists)
{
    // Note that these loops will also include itself
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            for (int dk = -1; dk <= 1; dk++)
            {
                int i = m_index[0] + di;
                int j = m_index[1] + dj;
                int k = m_index[2] + dk;

                // PBC
                if (i < 0) i += nLists[0];
                else if (i >= nLists[0]) i -= nLists[0];
                if (j < 0) j += nLists[1];
                else if (j >= nLists[1]) j -= nLists[1];
                if (k < 0) k += nLists[2];
                else if (k >= nLists[2]) k -= nLists[2];

                int linearIndex = convert3dIndicesToLinearIndex(i, j, k, nLists);

                if (std::find(m_neighbors.begin(), m_neighbors.end(), &lists[linearIndex]) == m_neighbors.end()) // Skip boxes already in list. Only does something for systems with less than 27 boxes.
                {
                    m_neighbors.push_back(&lists[linearIndex]);
                }

                // find m_displacementVectors
            }
        }
    }
}

void NeighborList::calculateForces(Force *force)
{
    for (Atom *atom : m_atoms)
    {
        for (NeighborList *list : m_neighbors)
        {
            if (list == this)
            {
                list->calcuateForcesFromSelf(atom, force);
            }
            else
            {
                list->calcuateForcesFromBox(atom, force);
            }
        }
    }
}

void NeighborList::purgeAtoms(std::list<Atom*>& atomsOutsideBox)
{
    auto atom = m_atoms.begin();
    while (atom != m_atoms.end())
    {
        if (
                ((*atom)->getPosition()[0] < m_displacement[0]) ||
                ((*atom)->getPosition()[0] >= (m_displacement[0]+m_boxSize[0])) ||
                ((*atom)->getPosition()[1] < m_displacement[1]) ||
                ((*atom)->getPosition()[1] >= (m_displacement[1]+m_boxSize[1])) ||
                ((*atom)->getPosition()[2] < m_displacement[2]) ||
                ((*atom)->getPosition()[2] >= (m_displacement[2]+m_boxSize[2]))
            )  // Atom is outside my box
        {
            atomsOutsideBox.push_back(*atom);
            atom = m_atoms.erase(atom); // Returns iterator pointing to item after the erased
        }
        else // Atom is inside my box
        {
            ++atom; // Go to next atom if the current one was still in box
        }
    }
}

void NeighborList::findMyAtomsInList(std::list<Atom*> &atoms)
{
    auto atom = atoms.begin();
    while (atom != atoms.end())
    {
        if (
                ((*atom)->getPosition()[0] >= m_displacement[0]) &&
                ((*atom)->getPosition()[0] < (m_displacement[0]+m_boxSize[0])) &&
                ((*atom)->getPosition()[1] >= m_displacement[1]) &&
                ((*atom)->getPosition()[1] < (m_displacement[1]+m_boxSize[1])) &&
                ((*atom)->getPosition()[2] >= m_displacement[2]) &&
                ((*atom)->getPosition()[2] < (m_displacement[2]+m_boxSize[2]))
            ) // Atom is inside my box
        {
            m_atoms.push_back(*atom); // Add to my list of atoms
            atom = atoms.erase(atom); // Returns iterator pointing to item after the erased
        }
        else // Atom is outside my box
        {
            ++atom; // Go to next atom if the current one didn't belong in my box
        }
    }
}

const std::list<Atom*>&NeighborList::getAtoms() const
{
    return m_atoms;
}

int NeighborList::getLinearIndex() const
{
    return m_linearIndex;
}

void NeighborList::calcuateForcesFromBox(Atom* atom1, Force* force)
{
    for (Atom *atom2 : m_atoms)
    {
        force->calculateForces(atom1, atom2);
    }
}

void NeighborList::calcuateForcesFromSelf(Atom* atom1, Force* force)
{
    for (Atom *atom2 : m_atoms)
    {
        if (atom1 != atom2)
        {
            force->calculateForces(atom1, atom2);
        }
        else
        {
            // skip calculation, since atom1 == atom2
        }
    }
}
