#ifndef MATRIX3_H
#define MATRIX3_H

#include "../vector.h"
#include "matrix2.h"

/* Holds a 3x3 row major matrix representing a transformation 
   in 3D space that does not include a translational component. 
   This matrix is not passed to produce an ligned structe. */
struct Matrix3
{
    real data[9];
};

/* Transform the given vector by this matrix. */
constexpr Vector3 operator*(const Matrix3 &m, const Vector3 &v)
{
    return Vector3{v.x * m.data[0] + v.y * m.data[1] + v.z * m.data[2],
                   v.x * m.data[3] + v.y * m.data[4] + v.z * m.data[5],
                   v.x * m.data[6] + v.y * m.data[7] + v.z * m.data[8]};
}

/* Return the matrix multiplied by a scalar value. */
constexpr Matrix3 operator*(const Matrix3 &m, real r)
{
    return Matrix3{m.data[0] * r, m.data[1] * r, m.data[2] * r,
                   m.data[3] * r, m.data[4] * r, m.data[5] * r,
                   m.data[6] * r, m.data[7] * r, m.data[8] * r};
}

/* Returns a matrix, which is this one multiplied by the other given matrix. */
constexpr Matrix3 operator*(const Matrix3 &l, const Matrix3 &r)
{
    return Matrix3{l.data[0] * r.data[0] + l.data[1] * r.data[3] + l.data[2] * r.data[6],
                   l.data[0] * r.data[1] + l.data[1] * r.data[4] + l.data[2] * r.data[7],
                   l.data[0] * r.data[2] + l.data[1] * r.data[5] + l.data[2] * r.data[8],
                   l.data[3] * r.data[0] + l.data[4] * r.data[3] + l.data[5] * r.data[6],
                   l.data[3] * r.data[1] + l.data[4] * r.data[4] + l.data[5] * r.data[7],
                   l.data[3] * r.data[2] + l.data[4] * r.data[5] + l.data[5] * r.data[8],
                   l.data[6] * r.data[0] + l.data[7] * r.data[3] + l.data[8] * r.data[6],
                   l.data[6] * r.data[1] + l.data[7] * r.data[4] + l.data[8] * r.data[7],
                   l.data[6] * r.data[2] + l.data[7] * r.data[5] + l.data[8] * r.data[8]};
}

/* Returns the determinant of the matrix. */
constexpr real determinant(const Matrix3 &m)
{
    real d_0 = m.data[4] * m.data[8] - m.data[5] * m.data[7];
    real d_1 = m.data[3] * m.data[8] - m.data[5] * m.data[6];
    real d_2 = m.data[3] * m.data[7] - m.data[5] * m.data[6];
    return m.data[0] * d_0 - m.data[1] * d_1 + m.data[2] * d_2;
}

/* Returns a new matrix containing the transpose of this matrix. */
constexpr Matrix3 transposed(const Matrix3 &m)
{
    return Matrix3{m.data[0], m.data[3], m.data[6],
                   m.data[1], m.data[4], m.data[7],
                   m.data[2], m.data[5], m.data[8]};
}

/* Return a new matrix containing the inverse of this matrix. */
constexpr Matrix3 inverse(const Matrix3 &m)
{
    Matrix3 minors = Matrix3{
        determinant(Matrix2{m.data[4], m.data[5], m.data[7], m.data[8]}),
        determinant(Matrix2{m.data[3], m.data[5], m.data[6], m.data[8]}),
        determinant(Matrix2{m.data[3], m.data[4], m.data[6], m.data[7]}),
        determinant(Matrix2{m.data[1], m.data[2], m.data[7], m.data[8]}),
        determinant(Matrix2{m.data[0], m.data[2], m.data[6], m.data[8]}),
        determinant(Matrix2{m.data[0], m.data[1], m.data[6], m.data[7]}),
        determinant(Matrix2{m.data[1], m.data[2], m.data[4], m.data[5]}),
        determinant(Matrix2{m.data[0], m.data[2], m.data[3], m.data[5]}),
        determinant(Matrix2{m.data[0], m.data[1], m.data[3], m.data[4]}),
    };

    // Calculate the deteminant and make sure it is not zero.
    real det = m.data[0] * minors.data[0] - m.data[1] * minors.data[1] + m.data[2] * minors.data[2];
    if (det == 0)
        return Matrix3{};

    return transposed(minors) * (1 / det);
}

#endif // !MATRIX3_H