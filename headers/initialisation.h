#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "individual.h"

/* Initialisation Operation Functor */
void (*initialise)(Population *, int size);

void randomInitialisation(Population *, int size);

Population *createPopulation(int size);

#endif
