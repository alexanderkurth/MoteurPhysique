#ifndef VECTOR_H
#define VECTOR_H

#include "precision.h"

struct Vector3
{
    real x, y, z;
};

/* Addition operator, return the sum of two vectors. */
constexpr Vector3 operator+(const Vector3 &l, const Vector3 &r)
{
    return {l.x + r.x, l.y + r.y, l.z + r.z};
}

/* Substraction operator, return the difference of two vectors. */
constexpr Vector3 operator-(const Vector3 &l, const Vector3 &r)
{
    return {l.x - r.x, l.y - r.y, l.z - r.z};
}

/* Multiplication operator, return the vector multiplied by the given value. */
constexpr Vector3 operator*(const Vector3 &l, real r)
{
    return {l.x * r, l.y * r, l.z * r};
}

/* Division operator, return the vector divided by the given value. */
constexpr Vector3 operator/(const Vector3 &l, real r)
{
    return l * (1 / r);
}

/* Return the squared magnetude of the vector. */
constexpr real sqr_magnetude(const Vector3 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
/* Return the magnetude of the vector. */
inline real magnetude(const Vector3 &v)
{
    return real_sqrt(sqr_magnetude(v));
}

/* Return the inverted vector, or -vector. */
constexpr Vector3 inverted(const Vector3 &v)
{
    return {-v.x, -v.y, -v.z};
}

/* Return this vector as a unit vector. */
inline Vector3 normalize(const Vector3 &v)
{
    return v / magnetude(v);
}

/* Return the vector resulting in a component multiplication. */
constexpr Vector3 comp_product(const Vector3 &l, const Vector3 &r)
{
    return {l.x * r.x, l.y * r.y, l.z * r.z};
}

/* Return the vector resulting of vector multiplication. */
constexpr Vector3 vec_product(const Vector3 &l, const Vector3 &r)
{
    return {l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x};
}

/* Return the scalar product of two vectors. */
constexpr real scalar_product(const Vector3& l,const Vector3 &r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

#endif // !VECTOR_H