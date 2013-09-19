#ifndef FITNESSFUNCTION_H
#define FITNESSFUNCTION_H

#define DEFAULT_FITNESS 1e100

#include "population.h"

typedef struct {
  double min;
  double step;
  double max;
} Range;

/** Functor, Map an individual's genotype to a phenotype */
double (*evaluate)(Individual *);

/** Generates a two dimensional array of random test test cases for one variable functions */
double **generateTrainingCases(const char *, const Range*);

/** Helper Interpreter Function (code, inputs array, #inputs) */
double rpnInterpreter(const char *, const double *, const int);

/** Classic sextic regression problem */
double sexticFitnessFunction(Individual *);


#endif
