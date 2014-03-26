#ifndef LINEARINDEXFUNCTIONS_H
#define LINEARINDEXFUNCTIONS_H

#include <vector>

inline int convert3dIndicesToLinearIndex(std::vector<int> &indexVector, std::vector<int> &NxNyNz);
inline int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, const std::vector<int>& NxNyNz);
inline int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, int, int ny, int nz);

int convert3dIndicesToLinearIndex(std::vector<int> &indexVector, std::vector<int> &NxNyNz)
{
    return convert3dIndicesToLinearIndex(indexVector[0], indexVector[1], indexVector[2], NxNyNz[0], NxNyNz[1], NxNyNz[2]);
}

int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, const std::vector<int> &NxNyNz)
{
    return convert3dIndicesToLinearIndex(indexX, indexY, indexZ, NxNyNz[0], NxNyNz[1], NxNyNz[2]);
}

int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, int /*nx*/, int ny, int nz)
{
    /* Converts 3d indices to linear index */
    return indexX*ny*nz + indexY*nz + indexZ;
}

#endif // LINEARINDEXFUNCTIONS_H
