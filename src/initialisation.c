#include <stdlib.h>
#include <confuse.h>

#include "initialisation.h"
#include "util.h"

extern cfg_t *config;

Genotype **createGenotypes(int number) {
  Genotype *genotypes = (Genotype *) malloc(number*sizeof(Genotype));
  Genotype **population = (Genotype **) malloc(number*sizeof(Genotype*));
  
  int i;
  int initialSize = cfg_getint(config, "maxInitialSize");
  for (i = 0; i < number; i++) {
    (genotypes+i)->codons = (unsigned int*) malloc(initialSize*sizeof(unsigned int));
    population[i] = (genotypes+i);
  }

  return population;
}

/* Random initialisation */
void randomInitialisation(Genotype **population, int number) {
  int maxInitialSize = cfg_getint(config, "maxInitialSize");

  int i,j;
  for (i = 0; i < number; i++) {
    int limit = randnSafe(maxInitialSize);
    for (j = 0; j < limit; j++)
      population[i]->codons[j] = rand();
    population[i]->length = limit;
  }
}
