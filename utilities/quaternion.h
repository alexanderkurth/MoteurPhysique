#ifndef QUATERNION_H
#define QUATERNION_H

struct Quaternion
{
    real r, i, j, k;
};

/* Component multiplication by a scalar. */
constexpr Quaternion operator*(const Quaternion &q, real r)
{
    return Quaternion{q.r * r, q.i * r, q.j * r, q.k * r};
}

/* Return the sum of two quaternions. */
constexpr Quaternion operator+(const Quaternion &l, const Quaternion &r)
{
    return Quaternion{l.r + r.r, l.i + r.i, l.j + r.j, l.k + r.k};
}

/* Return the product of the left quaternion and the right quaternion. */
constexpr Quaternion operator*(const Quaternion &l, const Quaternion &r)
{
    return Quaternion{l.r * r.r - l.i * r.i - l.j * r.j - l.k * r.k,
                      l.r * r.i + l.i * r.r + l.j * r.k - l.k * r.j,
                      l.r * r.j + l.j * r.r + l.k * r.i - l.i * r.k,
                      l.r * r.k + l.k * r.r + l.i * r.j - l.j * r.i};
}

/* Normalize the quaternion to maintain its value as an angle. */
inline Quaternion normalize(const Quaternion &q)
{
    real sqr_magnetude = q.r * q.r + q.i * q.i + q.j * q.j + q.k * q.k;
    if (sqr_magnetude == 0)
        return q;
    return q * (1 / real_sqrt(sqr_magnetude));
}

/* Add a vector onto the quaternion. */
inline Quaternion operator+(const Quaternion &q, const Vector3 &v)
{
    Quaternion qv = Quaternion{0, v.x, v.y, v.z} * q;
    Quaternion result = q + (qv * 0.5);
    return normalize(result);
}

#endif // !QUATERNION_H