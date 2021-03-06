#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "population.h"

/* Initialisation Operation Functor */
void (*initialise)(Population *p, int size);

void randomInitialisation(Population *p, int size);

Population *createPopulation(int size);

#endif
