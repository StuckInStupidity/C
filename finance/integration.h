include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

#ifndef INTEGRATION_H
#define INTEGRATION_H


typedef struct{
  char name[20];
} QuadFormula;

#ifdef INTEGRATION_C

#else /* INTEGRATION_C */

/* Declaration of the functions to code */

extern bool setQuadFormula(QuadFormula* qf, char* name);
extern void printQuadFormula(QuadFormula* qf); /* Not required but useful for debugging */

/* Returns the integral of function f from a to b. The approximation is done by splitting
   the interval [a,b] in N subdivisions, and then using the quadrature formula defined by qf */
extern double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf);

/* Same as function integrate, except that the number N of subdivision is computed using the
   argument dx: we take N = |b-a|/dx (rounded to be an integer) */
extern double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf);

#endif /* INTEGRATION_C */

#endif /* INTEGRATION_H */