#include <stdlib.h>

#include "config.h"
#include "initialisation.h"
#include "util.h"

Genotype **createGenotypes(int number) {
  Genotype *genotypes = (Genotype *) malloc(number*sizeof(Genotype));
  Genotype **population = (Genotype **) malloc(number*sizeof(Genotype*));
  
  int i;
  for (i = 0; i < number; i++) {
    (genotypes+i)->codons = (unsigned int*) malloc(config.maxInitialSize*sizeof(unsigned int));
    population[i] = (genotypes+i);
  }

  return population;
}

/* Random initialisation */
void randomInitialisation(Genotype **population, int number) {
  int i,j;
  for (i = 0; i < number; i++) {
    int limit = randnSafe(config.maxInitialSize);
    for (j = 0; j < limit; j++)
      population[i]->codons[j] = rand();
    population[i]->length = limit;
  }
}
