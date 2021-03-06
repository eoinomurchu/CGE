#include <stdlib.h>

#include "config.h"
#include "initialisation.h"
#include "util.h"

Genotype *createGenotype() {
  Genotype *genotype = (Genotype *) malloc(sizeof(Genotype));
  genotype->codons = (unsigned int*) malloc(config.maxInitialSize*sizeof(unsigned int));
  return genotype;
}

Population *createPopulation(int size) {
  int i;

  Population *pop = malloc(sizeof(Population));
  pop->inds = malloc(size*sizeof(Individual*));
  pop->size = size;
  
  for (i = 0; i < size; i++) {
    pop->inds[i] = (Individual *) malloc(sizeof(Individual));
    pop->inds[i]->genotype = createGenotype();
    pop->inds[i]->phenotype = NULL;
    pop->inds[i]->derivationTree = NULL;
  }

  return pop;
}

/* Random initialisation */
void randomInitialisation(Population *population, int size) {
  int i,j;
  for (i = 0; i < size; i++) {
    int limit = randnSafe(config.maxInitialSize);
    for (j = 0; j < limit; j++)
      population->inds[i]->genotype->codons[j] = rand();
    population->inds[i]->genotype->length = limit;
    population->inds[i]->phenotype = NULL;
    population->inds[i]->derivationTree = NULL;
  }
}
