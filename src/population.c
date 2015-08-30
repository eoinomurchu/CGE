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
static Phenotype *copyPhenotype(Phenotype *phenotype) {
  if (phenotype == NULL) return NULL;
  return strdup(phenotype);
}

/*
 *
 */
Individual *copyIndividual(Individual *individual) {
  Individual *newIndividual = malloc(sizeof(Individual));
  newIndividual->valid = individual->valid;
  newIndividual->fitness = individual->fitness;
  newIndividual->genotype = copyGenotype(individual->genotype);
  newIndividual->phenotype = copyPhenotype(individual->phenotype);
  /* TODO copy tree */
  newIndividual->derivationTree = NULL;

  return newIndividual;
}

/*
 *
 */
Population *copyPopulation(Population* population) {
  int i;

  Population *newPopulation = malloc(sizeof(Population));
  newPopulation->inds =  malloc(population->size * sizeof(Individual*));
  newPopulation->size = population->size;

  for (i = 0; i < newPopulation->size; i++)
    newPopulation->inds[i] = copyIndividual(population->inds[i]);

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
void printIndividual(Individual *individual) {
  int c;
  for (c = 0; c < individual->genotype->length; c++)
    printf("%d ", individual->genotype->codons[c]);
  printf("\n");
  if (!individual->valid)
    printf("\tINVALID\n");
  else if (individual->phenotype == NULL)
    printf("\tNOTMAPPED\n");
  else
    printf("\t%s\n", individual->phenotype);
}

/*
 *
 */
void printPopulation(Population *population) {
  int i;
  for (i = 0; i < population->size; i++) {
    printf("%d:\t", i);
    printIndividual(population->inds[i]);
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
