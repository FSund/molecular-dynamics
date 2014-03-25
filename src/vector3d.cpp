#include "vector3d.h"

std::ostream& operator<< (std::ostream &out, const Vector3D &vector)
{
    out << vector.mem_local[0] << ", " << vector.mem_local[1] << ", " << vector.mem_local[2];
    return out;
}
