#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "population.h"

/*
 *
 */
static Genotype *copyGenotype(Genotype *genotype) {
  Genotype *newGenotype = malloc(sizeof(Genotype));
  newGenotype->length = genotype->length;
  newGenotype->maxLength = genotype->length;
  newGenotype->encodingLength = genotype->encodingLength;

  newGenotype->codons = (unsigned int*) malloc(genotype->length*sizeof(unsigned int));
  memcpy(newGenotype->codons, genotype->codons, genotype->length*sizeof(unsigned int));

  return newGenotype;
}

/*
 *
 */
Individual *copyIndividual(Individual *individual) {
  Individual *newIndividual = malloc(sizeof(Individual));
  newIndividual->valid = individual->valid;
  newIndividual->fitness = individual->fitness;
  newIndividual->genotype = copyGenotype(individual->genotype);
  /* TODO copy phenotype and tree */
  newIndividual->phenotype = NULL;
  newIndividual->derivationTree = NULL;

  return newIndividual;
}

/*
 *
 */
Population *copyPopulation(Population* population) {
  int i, c;

  Population *newPopulation = malloc(sizeof(Population));
  newPopulation->inds =  malloc(population->size * sizeof(Individual*));
  newPopulation->size = population->size;

  for (i = 0; i < newPopulation->size; i++) {
    newPopulation->inds[i] = copyIndividual(population->inds[i]);

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

/*
 *
 */
void clearPopulation(Population *population) {
  int i;
  for (i = 0; i < population->size; i++) {
    if (population->inds[i]->derivationTree)
      clearTree(population->inds[i]->derivationTree);
    if (population->inds[i]->phenotype)
      free(population->inds[i]->phenotype);
    if (population->inds[i]->genotype) {
      if (population->inds[i]->genotype->codons)
	free(population->inds[i]->genotype->codons);
      free(population->inds[i]->genotype);
    }
    free(population->inds[i]);
  }
  free(population->inds);
  free(population);
}

/*
 *
 */
void printPopulation(Population *population) {
  int i, c;
  for (i = 0; i < population->size; i++) {
    printf("%d:\t", i);
    for (c = 0; c < population->inds[i]->genotype->length; c++)
      printf("%d ", population->inds[i]->genotype->codons[c]);
    printf("\n");
    if (population->inds[i]->valid)
      printf("\t%s\n", population->inds[i]->phenotype);
  }
}

/*
 *
 */
Individual *findBestIndiviual(Population *population) {
  int i;
  Individual *best, *curr;
  
  curr = best = population->inds[0];
  for (i = 1; i < population->size; i++) {
    curr = population->inds[i];
    if (curr->valid && curr->fitness < best->fitness)
      best = curr;
  }
  return best;
}
