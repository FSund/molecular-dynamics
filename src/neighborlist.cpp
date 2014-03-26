#include <neighborlist.h>

Vector3D NeighborList::m_boxSize;
const Vector3D NeighborList::zeroVec = Vector3D(0.0, 0.0, 0.0);

NeighborList::NeighborList(
        const Vector3D &origin,
        const std::vector<Atom *> &atoms,
        const std::vector<int> &index,
        const int linearIndex):
//    system(system),
    m_atoms(std::list<Atom *>(atoms.begin(), atoms.end())), // "Converting" std::vector to std::list
    m_origin(origin),
    m_index(index),
    m_linearIndex(linearIndex)
{
}

void NeighborList::findNeighbors(
        std::vector<NeighborList> &lists, // This can't be const because m_neighbors.push_back(&lists[linearIndex]) doesn't like it
        const std::vector<int> &nLists,
        const Vector3D &systemSize)
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

                NeighborList *neighborList = &lists[linearIndex];
                if (std::find(m_neighbors.begin(), m_neighbors.end(), neighborList) == m_neighbors.end()) // Skip boxes already in list. Only does something for systems with less than 27 boxes.
                {
                    m_neighbors.push_back(neighborList);
                }

                // Calculate displacement vector for this neighbor
                Vector3D displacementVector(0.0, 0.0, 0.0);
                Vector3D drVec = m_origin - neighborList->m_origin;
                for (uint dim = 0; dim < 3; dim++)
                {
                    if (drVec[dim] >= systemSize[dim]/2.0)
                    {
                        displacementVector[dim] -= systemSize[dim];
                    }
                    else if (drVec[dim] < -systemSize[dim]/2.0)
                    {
                        displacementVector[dim] += systemSize[dim];
                    }
                }
                m_displacementVectors.push_back(displacementVector);
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
                ((*atom)->getPosition()[0] < m_origin[0]) ||
                ((*atom)->getPosition()[0] >= (m_origin[0]+m_boxSize[0])) ||
                ((*atom)->getPosition()[1] < m_origin[1]) ||
                ((*atom)->getPosition()[1] >= (m_origin[1]+m_boxSize[1])) ||
                ((*atom)->getPosition()[2] < m_origin[2]) ||
                ((*atom)->getPosition()[2] >= (m_origin[2]+m_boxSize[2]))
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
                ((*atom)->getPosition()[0] >= m_origin[0]) &&
                ((*atom)->getPosition()[0] < (m_origin[0]+m_boxSize[0])) &&
                ((*atom)->getPosition()[1] >= m_origin[1]) &&
                ((*atom)->getPosition()[1] < (m_origin[1]+m_boxSize[1])) &&
                ((*atom)->getPosition()[2] >= m_origin[2]) &&
                ((*atom)->getPosition()[2] < (m_origin[2]+m_boxSize[2]))
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

void NeighborList::calculateForces(Force *force)
{
    for (auto atom = m_atoms.begin(); atom != m_atoms.end(); ++atom) // Use iterators so we can calculate force from self efficiently (start from iterator atom+1)
    {
        for (uint i = 0; i < m_neighbors.size(); i++)
        {
            if (m_neighbors[i] == this)
            {
                m_neighbors[i]->calcuateForcesFromSelfIterator(atom, force);
            }
            else
            {
                m_neighbors[i]->calcuateForcesFromBox(*atom, force, m_displacementVectors[i]);
            }
        }
    }
}

inline void NeighborList::calcuateForcesFromSelfIterator(const std::list<Atom *>::iterator &atom1, Force* force)
{
    auto tmp = atom1; // Make copy since we can't increment atom1
    for (auto atom2 = ++tmp; atom2 != m_atoms.end(); ++atom2)
    {
        force->calculateForces(*atom1, *atom2, zeroVec);
    }
}

inline void NeighborList::calcuateForcesFromSelf(Atom* atom1, Force* force)
{
    for (Atom *atom2 : m_atoms)
    {
        if (atom1 != atom2)
        {
            force->calculateForces(atom1, atom2, Vector3D(0.0, 0.0, 0.0));
        }
        else
        {
            // skip calculation, since atom1 == atom2
        }
    }
}

inline void NeighborList::calcuateForcesFromBox(Atom* atom1, Force* force, const Vector3D &displacementVector)
{
    for (Atom *atom2 : m_atoms)
    {
        force->calculateForces(atom1, atom2, displacementVector);
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
