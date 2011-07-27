#ifndef GENOPS_H
#define GENOPS_H

#include "genotype.h"

/* Mutation Operation Functor */
void (*mutate)(Genotype *);

void intflipMutation(Genotype *);

/* Crossover Operation Functor */
void (*crossover)(Genotype *, Genotype *);

void onepointCrossover(Genotype *, Genotype *);

#endif
