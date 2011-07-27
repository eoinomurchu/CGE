#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "individual.h"

/* Initialisation Operation Functor */
void (*initialise)(Genotype **, int number);

void randomInitialisation(Genotype **population, int number);

Genotype **createGenotypes(int number);

#endif
