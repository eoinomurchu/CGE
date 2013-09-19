#ifndef GENOPS_H
#define GENOPS_H

#include "population.h"

/*
 * Operator Functor - Integer Flip Mutation
 */
Population *intflipMutationOperator(Population *, Population *);

/*
 * Operator Functor - One Point Crossover
 */
Population *onepointCrossoverOperator(Population *, Population *);

#endif
