#ifndef FITNESSFUNCTION_H
#define FITNESSFUNCTION_H

#include "population.h"

/** Functor, Map an individual's genotype to a phenotype */
float (*evaluate)(Individual *);

#endif
