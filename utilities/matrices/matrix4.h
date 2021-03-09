#ifndef MATRIX4_H
#define MATRIX4_H

#include "matrix3.h"

/* Holds a transform matrix, consisting of roation matrix and a
   position. The matrix has 12 elements, and it is assumed the
   the remaining four are (0,0,0,1), producing a homogenous matrix. */
struct Matrix4
{
    real data[16];
};

/* Transform the given vector by this matrix. */
constexpr Vector3 transform_point(const Matrix4 &m, const Vector3 &v)
{
    return Vector3{v.x * m.data[0] + v.y * m.data[1] + v.z * m.data[2] + m.data[3],
                   v.x * m.data[4] + v.y * m.data[5] + v.z * m.data[6] + m.data[7],
                   v.x * m.data[8] + v.y * m.data[9] + v.z * m.data[10] + m.data[11]};
}

/* Transform the given direction vector by a 4x4 matrix. */
constexpr Vector3 transform_dir(const Matrix4 &m, const Vector3 &v)
{
    return Vector3{m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z,
                   m.data[3] * v.x + m.data[4] * v.y + m.data[5] * v.z,
                   m.data[6] * v.x + m.data[7] * v.y + m.data[8] * v.z};
}

/* Transform the given vector by this matrix. */
constexpr Matrix4 operator*(const Matrix4 &m, real r)
{
    return Matrix4{m.data[0] * r, m.data[1] * r, m.data[2] * r, m.data[3] * r,
                   m.data[4] * r, m.data[5] * r, m.data[6] * r, m.data[7] * r,
                   m.data[8] * r, m.data[9] * r, m.data[10] * r, m.data[11] * r,
                   m.data[12] * r, m.data[13] * r, m.data[14] * r, m.data[15] * r};
}

/* Return a matrix, which is this one multiplied by the other given matrix. */
constexpr Matrix4 operator*(const Matrix4 &l, const Matrix4 &r)
{
    return Matrix4{r.data[0] * l.data[0] + r.data[4] * l.data[1] + r.data[8] * l.data[2] + r.data[12] * l.data[3],
                   r.data[1] * l.data[0] + r.data[5] * l.data[1] + r.data[9] * l.data[2] + r.data[13] * l.data[3],
                   r.data[2] * l.data[0] + r.data[6] * l.data[1] + r.data[10] * l.data[2] + r.data[14] * l.data[3],
                   r.data[3] * l.data[0] + r.data[7] * l.data[1] + r.data[11] * l.data[2] + r.data[15] * l.data[3],
                   r.data[0] * l.data[4] + r.data[4] * l.data[5] + r.data[8] * l.data[6] + r.data[12] * l.data[7],
                   r.data[1] * l.data[4] + r.data[5] * l.data[5] + r.data[9] * l.data[6] + r.data[13] * l.data[7],
                   r.data[2] * l.data[4] + r.data[6] * l.data[5] + r.data[10] * l.data[6] + r.data[14] * l.data[7],
                   r.data[3] * l.data[4] + r.data[7] * l.data[5] + r.data[11] * l.data[6] + r.data[15] * l.data[7],
                   r.data[0] * l.data[8] + r.data[4] * l.data[9] + r.data[8] * l.data[10] + r.data[12] * l.data[11],
                   r.data[1] * l.data[8] + r.data[5] * l.data[9] + r.data[9] * l.data[10] + r.data[13] * l.data[11],
                   r.data[2] * l.data[8] + r.data[6] * l.data[9] + r.data[10] * l.data[10] + r.data[14] * l.data[11],
                   r.data[3] * l.data[8] + r.data[7] * l.data[9] + r.data[11] * l.data[10] + r.data[15] * l.data[11],
                   r.data[0] * l.data[12] + r.data[4] * l.data[13] + r.data[8] * l.data[14] + r.data[12] * l.data[15],
                   r.data[1] * l.data[12] + r.data[5] * l.data[13] + r.data[9] * l.data[14] + r.data[13] * l.data[15],
                   r.data[2] * l.data[12] + r.data[6] * l.data[13] + r.data[10] * l.data[14] + r.data[14] * l.data[15],
                   r.data[3] * l.data[12] + r.data[7] * l.data[13] + r.data[11] * l.data[14] + r.data[15] * l.data[15]};
}

/* Returns the determinant of the matrix. */
constexpr real determinant(const Matrix4 &m)
{
    Matrix3 minor_0 = Matrix3{m.data[5], m.data[6], m.data[7], m.data[9], m.data[10], m.data[11], m.data[13], m.data[14], m.data[15]};
    Matrix3 minor_1 = Matrix3{m.data[4], m.data[6], m.data[7], m.data[8], m.data[10], m.data[11], m.data[12], m.data[14], m.data[15]};
    Matrix3 minor_2 = Matrix3{m.data[4], m.data[5], m.data[7], m.data[8], m.data[9], m.data[11], m.data[12], m.data[13], m.data[15]};
    Matrix3 minor_3 = Matrix3{m.data[4], m.data[5], m.data[6], m.data[8], m.data[9], m.data[10], m.data[12], m.data[13], m.data[14]};
    return m.data[0] * determinant(minor_0) - m.data[1] * determinant(minor_1) + m.data[2] * determinant(minor_2) - m.data[3] * determinant(minor_3);
}

/* Returns a new matrix containing the transpose of this matrix. */
constexpr Matrix4 transposed(const Matrix4 &m)
{
    return Matrix4{m.data[0], m.data[3], m.data[6], m.data[9],
                   m.data[1], m.data[4], m.data[7], m.data[10],
                   m.data[2], m.data[5], m.data[8], m.data[11],
                   m.data[12], m.data[13], m.data[14], m.data[15]};
}

/* Returns a new matrix which is the inverse of this matrix. */
constexpr Matrix4 inverse(const Matrix4 &m)
{
    Matrix4 minors = Matrix4{determinant(Matrix3{m.data[5], m.data[6], m.data[7], m.data[9], m.data[10], m.data[11], m.data[13], m.data[14], m.data[15]}),
                             determinant(Matrix3{m.data[4], m.data[6], m.data[7], m.data[8], m.data[10], m.data[11], m.data[12], m.data[14], m.data[15]}),
                             determinant(Matrix3{m.data[4], m.data[5], m.data[7], m.data[8], m.data[9], m.data[11], m.data[12], m.data[13], m.data[15]}),
                             determinant(Matrix3{m.data[4], m.data[5], m.data[6], m.data[8], m.data[9], m.data[10], m.data[12], m.data[13], m.data[14]}),
                             determinant(Matrix3{m.data[1], m.data[2], m.data[3], m.data[9], m.data[10], m.data[11], m.data[13], m.data[14], m.data[15]}),
                             determinant(Matrix3{m.data[0], m.data[2], m.data[3], m.data[8], m.data[10], m.data[11], m.data[12], m.data[14], m.data[15]}),
                             determinant(Matrix3{m.data[0], m.data[1], m.data[3], m.data[8], m.data[9], m.data[11], m.data[12], m.data[13], m.data[15]}),
                             determinant(Matrix3{m.data[0], m.data[1], m.data[2], m.data[8], m.data[9], m.data[10], m.data[12], m.data[13], m.data[14]}),
                             determinant(Matrix3{m.data[1], m.data[2], m.data[3], m.data[5], m.data[6], m.data[7], m.data[13], m.data[14], m.data[15]}),
                             determinant(Matrix3{m.data[0], m.data[2], m.data[3], m.data[4], m.data[6], m.data[7], m.data[12], m.data[14], m.data[15]}),
                             determinant(Matrix3{m.data[0], m.data[1], m.data[3], m.data[4], m.data[5], m.data[7], m.data[12], m.data[13], m.data[15]}),
                             determinant(Matrix3{m.data[0], m.data[1], m.data[2], m.data[4], m.data[5], m.data[6], m.data[12], m.data[13], m.data[14]}),
                             determinant(Matrix3{m.data[1], m.data[2], m.data[3], m.data[5], m.data[6], m.data[7], m.data[9], m.data[10], m.data[11]}),
                             determinant(Matrix3{m.data[0], m.data[2], m.data[3], m.data[4], m.data[6], m.data[7], m.data[8], m.data[10], m.data[11]}),
                             determinant(Matrix3{m.data[0], m.data[1], m.data[3], m.data[4], m.data[5], m.data[7], m.data[8], m.data[9], m.data[11]}),
                             determinant(Matrix3{m.data[0], m.data[1], m.data[2], m.data[4], m.data[5], m.data[6], m.data[8], m.data[9], m.data[10]})};

    real det = m.data[0] * minors.data[0] - m.data[1] * minors.data[1] + m.data[2] * minors.data[2] - m.data[3] * minors.data[3];
    if (det == 0)
        return Matrix4{};

    return transposed(minors) * (1 / det);
}

/* Return a 4x4 matrix used for scaling */
constexpr Matrix4 scale(const Vector3 &v)
{
    return Matrix4{v.x, 0, 0, 0,
                   0, v.y, 0, 0,
                   0, 0, v.z, 0,
                   0, 0, 0, 1};
}

/* Create a translation matrix from a vector. */
constexpr Matrix4 make_translate(const Vector3 &v)
{
    return Matrix4{1, 0, 0, v.x,
                   0, 1, 0, v.y,
                   0, 0, 1, v.z,
                   0, 0, 0, 1};
}

/* Convert a 3x3 matrix into a 4x4 matrix. */
constexpr Matrix4 make_matrix4(const Matrix3 &m)
{
    return Matrix4{m.data[0], m.data[1], m.data[2], 0,
                   m.data[3], m.data[4], m.data[5], 0,
                   m.data[6], m.data[7], m.data[8], 0,
                   0, 0, 0, 1};
}

#endif // !MATRIX4_H