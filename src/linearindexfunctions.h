#ifndef LINEARINDEXFUNCTIONS_H
#define LINEARINDEXFUNCTIONS_H

#include <vector>

inline int convert3dIndicesToLinearIndex(std::vector<int> &indexVector, std::vector<int> &NxNyNz);
inline int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, const std::vector<int>& NxNyNz);
inline int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, int nx, int ny, int nz);

int convert3dIndicesToLinearIndex(std::vector<int> &indexVector, std::vector<int> &NxNyNz)
{
    return convert3dIndicesToLinearIndex(indexVector[0], indexVector[1], indexVector[2], NxNyNz[0], NxNyNz[1], NxNyNz[2]);
}

int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, const std::vector<int> &NxNyNz)
{
    return convert3dIndicesToLinearIndex(indexX, indexY, indexZ, NxNyNz[0], NxNyNz[1], NxNyNz[2]);
}

int convert3dIndicesToLinearIndex(int indexX, int indexY, int indexZ, int nx, int ny, int nz)
{
    /* Converts 3d indices to linear index */
    return indexX*ny*nz + indexY*nz + indexZ;
}

//inline int convert3dIndicesToLinearIndex(              int* index_vector, int *nx_ny_nz);
//inline int convert3dIndicesToLinearIndex(              int* index_vector, int nx, int ny, int nz);
//inline int convert3dIndicesToLinearIndex(              int index_x, int index_y, int index_z, int *nx_ny_nz);
//inline int convert3dIndicesToLinearIndex(              int index_x, int index_y, int index_z, int nx, int ny, int nz);

//inline int convert3dIndicesToLinearIndexInline(int index_x, int index_y, int index_z, int nx, int ny, int nz);

//inline void convertLinearIndexTo3dIndices(              int linear_index, int *nx_ny_nz,          int *index_vector);
//inline void convertLinearIndexTo3dIndices(              int linear_index, int nx, int ny, int nz, int *index_vector);
//inline void convertLinearIndexTo3dIndices(              int linear_index, int *nx_ny_nz,          int &index_x, int &index_y, int &index_z);

//inline void convertLinearIndexTo3dIndicesInline(int linear_index, int nx, int ny, int nz, int &index_x, int &index_y, int &index_z);

//inline int convert3dIndicesToLinearIndex(int* index_vector, int *nx_ny_nz) {
//    return convert3dIndicesToLinearIndexInline(index_vector[0], index_vector[1], index_vector[2], nx_ny_nz[0], nx_ny_nz[1], nx_ny_nz[2]);
//}

//inline int convert3dIndicesToLinearIndex(int* index_vector, int nx, int ny, int nz) {
//    return convert3dIndicesToLinearIndexInline(index_vector[0], index_vector[1], index_vector[2], nx, ny, nz);
//}

//inline int convert3dIndicesToLinearIndex(int index_x, int index_y, int index_z, int *nx_ny_nz) {
//    return convert3dIndicesToLinearIndexInline(index_x, index_y, index_z, nx_ny_nz[0], nx_ny_nz[1], nx_ny_nz[2]);
//}

//inline int convert3dIndicesToLinearIndex(int index_x, int index_y, int index_z, int nx, int ny, int nz) {
//    return convert3dIndicesToLinearIndexInline(index_x, index_y, index_z, nx, ny, nz);
//}

//inline void convertLinearIndexTo3dIndices(int linear_index, int *nx_ny_nz, int *index_vector) {
//    convertLinearIndexTo3dIndicesInline(linear_index, nx_ny_nz[0], nx_ny_nz[1], nx_ny_nz[2], index_vector[0], index_vector[1], index_vector[2]);
//}

//inline void convertLinearIndexTo3dIndices(int linear_index, int nx, int ny, int nz, int *index_vector) {
//    convertLinearIndexTo3dIndicesInline(linear_index, nx, ny, nz, index_vector[0], index_vector[1], index_vector[2]);
//}

//inline void convertLinearIndexTo3dIndices(int linear_index, int *nx_ny_nz, int &index_x, int &index_y, int &index_z) {
//    convertLinearIndexTo3dIndicesInline(linear_index, nx_ny_nz[0], nx_ny_nz[1], nx_ny_nz[2], index_x, index_y, index_z);
//}

//inline void convertLinearIndexTo3dIndices(int linear_index, int nx, int ny, int nz, int &index_x, int &index_y, int &index_z) {
//    convertLinearIndexTo3dIndicesInline(linear_index, nx, ny, nz, index_x, index_y, index_z);
//}


/*
 Below are "private" inline functions that are used by the functions above.
 This is so we get the functions inlined in the functions above, but only have
 to edit one function
*/

//inline int convert3dIndicesToLinearIndex(const int index_x, const int index_y, const int index_z, const int nx, const int ny, const int nz) {
//    /* Converts 3d indices to linear index */
//    return index_x*ny*nz + index_y*nz + index_z;
//}

//inline int convert3dIndicesToLinearIndex(int index_x, int index_y, int index_z, int nx, int ny, int nz) {
//    /* Converts 3d indices to linear index */
//    return index_x*ny*nz + index_y*nz + index_z;
//}


//inline void convertLinearIndexTo3dIndicesInline(int linear_index, int nx, int ny, int nz, int &index_x, int &index_y, int &index_z) {
//    /* Converts linear index to 3d indices */
//    index_x = linear_index/(ny*nz);   // Index in x-direction
//    index_y = (linear_index/nz)%ny;   // Index in y-direction
//    index_z = linear_index%nz;        // Index in z-direction
//}

#endif // LINEARINDEXFUNCTIONS_H
