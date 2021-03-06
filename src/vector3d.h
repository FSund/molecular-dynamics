#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <iostream>

class Vector3D
{
public:
    Vector3D();                             // default constructor
    Vector3D(double xpos, double ypos, double zpos);
    Vector3D(const Vector3D& point);        // copy constructor
//    ~Vector3D();

    // Default generated by compiler for C++98. Uncomment to see where used. Not shure if there's a point in defining our own??
//    Vector3D& operator=(const Vector3D&) = delete;   // copy assignment operator

    // default stuff generated by compile when using C++11. Uncomment to see where used. Not shure if there's a point in defining our own??
//    Vector3D(Vector3D&&) = delete;          // move constructor
//    Vector3D& operator=(Vector&&) = delete; // move-assign

//    bool isNull() const;

    double x() const;
    double y() const;
    double z() const;

    double& operator()(const int component);
    double& operator[](const int component);
    double operator()(const int component) const;
    double operator[](const int component) const;

    friend std::ostream& operator<< (std::ostream& out, const Vector3D& vector);

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double length() const;
    double lengthSquared() const;

//    Vector3D normalized() const;
//    void normalize();

    Vector3D& operator+=(const Vector3D& vector);
    Vector3D& operator-=(const Vector3D& vector);
    Vector3D& operator*=(double factor);
    Vector3D& operator*=(const Vector3D& vector);
    Vector3D& operator/=(double divisor);

//    static double dotProduct(const Vector3D& v1, const Vector3D& v2);
//    static Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2);
//    static Vector3D normal(const Vector3D& v1, const Vector3D& v2);
//    static Vector3D normal
//        (const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

//    double distanceToPlane(const Vector3D& plane, const Vector3D& normal) const;
//    double distanceToPlane(const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const;
//    double distanceToLine(const Vector3D& point, const Vector3D& direction) const;

    friend bool operator==(const Vector3D& v1, const Vector3D& v2);
    friend bool operator!=(const Vector3D& v1, const Vector3D& v2);
    friend const Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
    friend const Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
    friend const Vector3D operator*(double factor, const Vector3D& vector);
    friend const Vector3D operator*(const Vector3D& vector, double factor);
    friend const Vector3D operator*(const Vector3D& v1, const Vector3D& v2);
    friend const Vector3D operator-(const Vector3D& vector);
    friend const Vector3D operator/(const Vector3D& vector, double divisor);

//    friend inline bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2);

private:
//    double xp, yp, zp;
    double mem_local[3];
};

inline Vector3D::Vector3D()
{
    mem_local[0] = 0.0;
    mem_local[1] = 0.0;
    mem_local[2] = 0.0;
}

inline Vector3D::Vector3D(double xpos, double ypos, double zpos)
{
    mem_local[0] = xpos;
    mem_local[1] = ypos;
    mem_local[2] = zpos;
}

inline Vector3D::Vector3D(const Vector3D& point)
{
    mem_local[0] = point.x();
    mem_local[1] = point.y();
    mem_local[2] = point.z();
}

//inline Vector3D::~Vector3D()
//{
//}

//inline bool Vector3D::isNull() const
//{
//    return (xp) && qIsNull(yp) && qIsNull(zp);
//}

inline double Vector3D::x() const { return mem_local[0]; }
inline double Vector3D::y() const { return mem_local[1]; }
inline double Vector3D::z() const { return mem_local[2]; }

inline void Vector3D::setX(double x) { mem_local[0] = x; }
inline void Vector3D::setY(double y) { mem_local[1] = y; }
inline void Vector3D::setZ(double z) { mem_local[2] = z; }

inline double& Vector3D::operator[](const int component) { return mem_local[component]; }
inline double& Vector3D::operator()(const int component) { return mem_local[component]; }
inline double Vector3D::operator[](const int component) const { return mem_local[component]; }
inline double Vector3D::operator()(const int component) const { return mem_local[component]; }

inline double Vector3D::length() const
{
    return std::sqrt(lengthSquared());
}

inline double Vector3D::lengthSquared() const
{
    return    mem_local[0]*mem_local[0]
            + mem_local[1]*mem_local[1]
            + mem_local[2]*mem_local[2];

}

inline Vector3D& Vector3D::operator+=(const Vector3D& vector)
{
    mem_local[0] += vector.mem_local[0];
    mem_local[1] += vector.mem_local[1];
    mem_local[2] += vector.mem_local[2];

    return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& vector)
{
    mem_local[0] -= vector.mem_local[0];
    mem_local[1] -= vector.mem_local[1];
    mem_local[2] -= vector.mem_local[2];

    return *this;
}

inline Vector3D& Vector3D::operator*=(double factor)
{
    mem_local[0] *= factor;
    mem_local[1] *= factor;
    mem_local[2] *= factor;

    return *this;
}

inline Vector3D& Vector3D::operator*=(const Vector3D& vector)
{
    mem_local[0] *= vector.mem_local[0];
    mem_local[1] *= vector.mem_local[1];
    mem_local[2] *= vector.mem_local[2];

    return *this;
}

inline Vector3D& Vector3D::operator/=(double divisor)
{
    mem_local[0] /= divisor;
    mem_local[1] /= divisor;
    mem_local[2] /= divisor;

    return *this;
}

inline bool operator==(const Vector3D& v1, const Vector3D& v2)
{
    return     v1.mem_local[0] == v2.mem_local[0]
            && v1.mem_local[1] == v2.mem_local[1]
            && v1.mem_local[2] == v2.mem_local[2];
}

inline bool operator!=(const Vector3D& v1, const Vector3D& v2)
{
    return     v1.mem_local[0] != v2.mem_local[0]
            || v1.mem_local[1] != v2.mem_local[1]
            || v1.mem_local[2] != v2.mem_local[2];
}

inline const Vector3D operator+(const Vector3D& v1, const Vector3D& v2)
{
    return
        Vector3D(
            v1.mem_local[0] + v2.mem_local[0],
            v1.mem_local[1] + v2.mem_local[1],
            v1.mem_local[2] + v2.mem_local[2]
        );
}

inline const Vector3D operator-(const Vector3D& v1, const Vector3D& v2)
{
    return
        Vector3D(
            v1.mem_local[0] - v2.mem_local[0],
            v1.mem_local[1] - v2.mem_local[1],
            v1.mem_local[2] - v2.mem_local[2]
        );
}

inline const Vector3D operator*(double factor, const Vector3D& vector)
{
    return
        Vector3D(
            vector.mem_local[0] * factor,
            vector.mem_local[1] * factor,
            vector.mem_local[2] * factor
        );
}

inline const Vector3D operator*(const Vector3D& vector, double factor)
{
    return operator*(factor, vector);
}

inline const Vector3D operator*(const Vector3D& v1, const Vector3D& v2)
{
    return
        Vector3D(
            v1.mem_local[0] * v2.mem_local[0],
            v1.mem_local[1] * v2.mem_local[1],
            v1.mem_local[2] * v2.mem_local[2]
        );
}

inline const Vector3D operator-(const Vector3D& vector)
{
    return
        Vector3D(
            -vector.mem_local[0],
            -vector.mem_local[1],
            -vector.mem_local[2]
        );
}

inline const Vector3D operator/(const Vector3D& vector, double divisor)
{
    return
        Vector3D(
            vector.mem_local[0] / divisor,
            vector.mem_local[1] / divisor,
            vector.mem_local[2] / divisor
        );
}

//inline bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2)
//{
//    return qFuzzyCompare(v1.xp, v2.xp) &&
//           qFuzzyCompare(v1.yp, v2.yp) &&
//           qFuzzyCompare(v1.zp, v2.zp);
//}

#endif // VECTOR3D_H
