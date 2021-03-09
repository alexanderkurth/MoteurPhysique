#ifndef UTILITIES_H
#define UTILITIES_H

#include "matrices/matrix2.h"
#include "matrices/matrix3.h"
#include "matrices/matrix4.h"
#include "quaternion.h"
#include "vector.h"

/* Transform a local point into world coordinates through its respective transform matrix. */
constexpr Vector3 local_point_to_world(const Matrix4 &transform, const Vector3 &point)
{
    return transform_point(transform, point);
}

/* Transform a world point into local coordinated through its respective transform matrix. */
constexpr Vector3 world_point_to_local(const Matrix4 &transform, const Vector3 &point)
{
    return transform_point(inverse(transform), point);
}

/* Transform a local direction into world coordinates through its respective transform matrix. */
constexpr Vector3 local_dir_to_world(const Matrix4 &transform, const Vector3 &dir)
{
    return transform_dir(transform, dir);
}

/* Transform a world direction into local coordinated through its respective transform matrix. */
constexpr Vector3 world_dir_to_local(const Matrix4 &transform, const Vector3 &dir)
{
    return transform_dir(inverse(transform), dir);
}

/* Convert a quaternion into a 3x3 matrix. */
constexpr Matrix3 make_matrix3(const Quaternion &q)
{
    return Matrix3{1 - (2 * q.j * q.j + 2 * q.k * q.k),
                   2 * q.i * q.j + 2 * q.k * q.r,
                   2 * q.i * q.k - 2 * q.j * q.r,
                   2 * q.i * q.j - 2 * q.k * q.r,
                   1 - (2 * q.i * q.i + 2 * q.k * q.k),
                   2 * q.j * q.k + 2 * q.i * q.r,
                   2 * q.i * q.k + 2 * q.j * q.r,
                   2 * q.j * q.k - 2 * q.i * q.r,
                   1 - (2 * q.i * q.i + 2 * q.j * q.j)};
}

/* Convert a quaternion into a 4x4 matrix. */
constexpr Matrix4 make_matrix4(const Quaternion &q)
{
    return Matrix4{1 - (2 * q.j * q.j + 2 * q.k * q.k),
                   2 * q.i * q.j + 2 * q.k * q.r,
                   2 * q.i * q.k - 2 * q.j * q.r, 0,
                   2 * q.i * q.j - 2 * q.k * q.r,
                   1 - (2 * q.i * q.i + 2 * q.k * q.k),
                   2 * q.j * q.k + 2 * q.i * q.r, 0,
                   2 * q.i * q.k + 2 * q.j * q.r,
                   2 * q.j * q.k - 2 * q.i * q.r,
                   1 - (2 * q.i * q.i + 2 * q.j * q.j), 0,
                   0, 0, 0, 1};
}

/* Identity matrices. */
const Matrix2 identity_matrix2 = Matrix2{1, 0, 0, 1};
const Matrix3 identity_matrix3 = Matrix3{1, 0, 0, 0, 1, 0, 0, 0, 1};
const Matrix4 identity_matrix4 = Matrix4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

#endif // !UTILITIES_H