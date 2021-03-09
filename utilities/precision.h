#ifndef _PRECISION_H_
#define _PRECISION_H_

#include <math.h>

#define _MIN(a,b) (((a)<(b))?(a):(b))
#define _MAX(a,b) (((a)>(b))?(a):(b))

/* Defines a real number precision. 
   Either: float or double. */
typedef float real;

/* Square root function for single-precision real. */
inline float real_sqrt (float value) { return sqrtf (value); }
/* Power function for single-precision real. */
inline float real_pow (float base, float exp) { return powf (base, exp); }
/* Aboslute function for single-precision real. */
inline float real_abs (float value) { return fabsf (value); }
/* Cosine function for single-precision real. */
inline float real_cos (float value) { return cosf (value); }
/* Sine function for single-precision real. */
inline float real_sin (float value) { return sinf (value); }
/* Exponential function for single-precision real. */
inline float real_exp (float value) { return expf (value); }

/* Square root function for double-precision real. */
inline double real_sqrt (double value) { return sqrtf (value); }
/* Power function for double-precision real. */
inline double real_pow (double base, double exp) { return powf (base, exp); }
/* Aboslute function for double-precision real. */
inline double real_abs (double value) { return fabs (value); }
/* Cosine function for double-precision real. */
inline double real_cos (double value) { return cosf (value); }
/* Sine function for double-precision real. */
inline double real_sin (double value) { return sinf (value); }
/* Exponential function for double-precision real. */
inline double real_exp (double value) { return expf (value); }


#endif // !_PRECISION_H_