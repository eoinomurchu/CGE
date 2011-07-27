#include <stdlib.h>
#include <confuse.h>

#include "initialisation.h"

extern cfg_t *config;

Genotype **createGenotypes(int number) {
  int initialSize = cfg_getint(config, "maxInitialSize");

  unsigned int *codonBuffer = malloc(number*initialSize*sizeof(unsigned int));
  Genotype *genotypes = (Genotype *) malloc(number*sizeof(Genotype));
  Genotype **population = (Genotype **) malloc(number*sizeof(Genotype*));
  
  int i, delta;
  for (i = 0, delta = 0; i < number; i++, delta += initialSize) {
    (genotypes+i)->codons = (codonBuffer+delta);
    population[i] = (genotypes+i);
  }

  return population;;
}

/* Random initialisation */
void randomInitialisation(Genotype **population, int number) {
  int maxInitialSize = cfg_getint(config, "maxInitialSize");

  int i,j;
  for (i = 0; i < number; i++) {
    int limit = rand() % maxInitialSize;
    for (j = 0; j < limit; j++)
      population[i]->codons[j] = rand();
    population[i]->length = limit;
  }
}
