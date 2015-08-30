#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "genops.h"
#include "population.h"
#include "util.h"

/*
 * Operator/Operation function
 */
Population *intflipMutationOperator(Population *population) {
  int i, m;

  for (i = 0; i < population->size; i++)
    for (m = 0; m < config.mutationRate; m++) {
      population->inds[i]->genotype->codons[randn(population->inds[i]->genotype->length)] = rand();
      if (population->inds[i]->phenotype) {
	free(population->inds[i]->phenotype);
	population->inds[i]->phenotype = NULL;
      }
    }
  return population;
}

/*
 * Operation
 */
static void onepointCrossover(Genotype *parent, Genotype *spouse) {
  int parentPoint, spousePoint, parentLength, spouseLength;
  unsigned int *crossoverBuffer;

  /* Only crossover with a certain probability */
  if (randf() > config.crossoverProb)
    return;

  /* Get xo points - TODO get points from inside encoding region */
  parentPoint = randn(parent->length);
  spousePoint = randn(spouse->length);

  parentLength = parent->length - parentPoint;
  spouseLength = spouse->length - spousePoint;

  /* Increase chromosome capacity if required */
  if (parentPoint +  spouseLength > parent->maxLength) {
    parent->maxLength = parentPoint + spouseLength;
    parent->codons = (unsigned int *) realloc(parent->codons, parent->maxLength*sizeof(unsigned int));
  }
  if (spousePoint + parentLength > spouse->maxLength) {
    spouse->maxLength = spousePoint + parentLength;
    spouse->codons = (unsigned int*) realloc(spouse->codons, spouse->maxLength*sizeof(unsigned int));
  }

  /* Perfrom crossover using temp buffer */
  crossoverBuffer = malloc(parentLength*sizeof(unsigned int));
  memcpy(crossoverBuffer, (parent->codons + parentPoint), parentLength*sizeof(unsigned int));
  memcpy((parent->codons + parentPoint), (spouse->codons + spousePoint), spouseLength*sizeof(unsigned int));
  memcpy((spouse->codons + spousePoint), crossoverBuffer, parentLength*sizeof(unsigned int));
  free(crossoverBuffer);

  /* Update length */
  parent->length -= (parentLength - spouseLength);
  spouse->length += (parentLength - spouseLength);
}

/*
 * Operator Functor
 */
Population *onepointCrossoverOperator(Population *population) {
  int i;

  /* We can't crossover without at least two individuals */
  if (population->size > 1) {
    for (i = 0; i < population->size - 1; i += 2)
      if (randf() < config.crossoverProb) {
	onepointCrossover(population->inds[i]->genotype, population->inds[i+1]->genotype);

	if (population->inds[i]->phenotype) {
	  free(population->inds[i]->phenotype);
	  population->inds[i]->phenotype = NULL;
	}
	if (population->inds[i+1]->phenotype) {
	  free(population->inds[i+1]->phenotype);
	  population->inds[i+1]->phenotype = NULL;
	}
      }

    if (population->size % 2 == 1)
      if (randf() < config.crossoverProb) {
	int randIndex = randnSafe(i);
	onepointCrossover(population->inds[i]->genotype, population->inds[randIndex]->genotype);

	if (population->inds[i]->phenotype) {
	  free(population->inds[i]->phenotype);
	  population->inds[i]->phenotype = NULL;
	}
	if (population->inds[randIndex]->phenotype) {
	  free(population->inds[randIndex]->phenotype);
	  population->inds[randIndex]->phenotype = NULL;
	}
      }
  }
  return population;
}
