#include <stdlib.h>

#include "config.h"
#include "initialisation.h"
#include "util.h"

Genotype **createGenotypes(int size) {
  Genotype *genotypes = (Genotype *) malloc(size*sizeof(Genotype));
  Genotype **population = (Genotype **) malloc(size*sizeof(Genotype*));
  
  int i;
  for (i = 0; i < size; i++) {
    (genotypes+i)->codons = (unsigned int*) malloc(config.maxInitialSize*sizeof(unsigned int));
    population[i] = (genotypes+i);
  }

  return population;
}

Population *createPopulation(int size) {
  Population *pop = (Population *) malloc(size*sizeof(Individual));
  Genotype **genotypes = createGenotypes(size);
  int i;
  for (i = 0; i < size; i++)
    pop[i].genotype = genotypes[i];
  return pop;
}

/* Random initialisation */
void randomInitialisation(Population *population, int size) {
  int i,j;
  for (i = 0; i < size; i++) {
    int limit = randnSafe(config.maxInitialSize);
    for (j = 0; j < limit; j++)
      population[i].genotype->codons[j] = rand();
    population[i].genotype->length = limit;
  }
}