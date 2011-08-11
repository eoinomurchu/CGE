#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "population.h"

static Genotype *copyGenotype(Genotype *genotype) {
  Genotype *newGenotype = malloc(sizeof(Genotype));
  newGenotype->length = genotype->length;
  newGenotype->maxLength = genotype->length;
  newGenotype->encodingLength = genotype->encodingLength;

  newGenotype->codons = (unsigned int*) malloc(genotype->length*sizeof(unsigned int));
  memcpy(newGenotype->codons, genotype->codons, genotype->length*sizeof(unsigned int));
  
  return newGenotype;
}

Individual *copyIndividual(Individual *individual) {
  Individual *newIndividual = malloc(sizeof(Individual));
  newIndividual->valid = individual->valid;
  newIndividual->fitness = individual->fitness;
  newIndividual->genotype = copyGenotype(individual->genotype);

  return newIndividual;
}

Population *copyPopulation(Population* population) {
  Population *newPopulation = malloc(sizeof(Population));
  newPopulation->inds =  malloc(population->size * sizeof(Individual*));
  newPopulation->size = population->size;

  int i;
  for (i = 0; i < newPopulation->size; i++) {
    newPopulation->inds[i] = copyIndividual(population->inds[i]);
    
    int c;
    printf("%d:\t", i);
    for (c = 0; c < population->inds[i]->genotype->length; c++)
      printf("%d ", population->inds[i]->genotype->codons[c]);
    printf("\n");

    printf("%d:\t", i);
    for (c = 0; c < newPopulation->inds[i]->genotype->length; c++)
      printf("%d ", newPopulation->inds[i]->genotype->codons[c]);
    printf("\n");
  }

  return newPopulation;
}
