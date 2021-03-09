#ifndef MATRIX2_H
#define MATRIX2_H

/* Holds a 2x2 row major matrix. Currently only used to 
   calculate determinants of bigger matrices. */
struct Matrix2
{
    real data[4];
};

/* Returns the determinant of the matrix. */
constexpr real determinant(const Matrix2 &m)
{
    return m.data[0] * m.data[3] - m.data[1] * m.data[2];
}

#endif // !MATRIX2_H