#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "genops.h"
#include "util.h"

/*
 * Operator/Operation function
 */
Population *intflipMutationOperator(Population *population, Population *selectedPopulation) {
  int i, m;
  for (i = 0; i < selectedPopulation->size; i++)
    for (m = 0; m < config.mutationRate; m++)
      selectedPopulation->inds[i]->genotype->codons[randn(selectedPopulation->inds[i]->genotype->length)] = rand();

  return selectedPopulation;
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
Population *onepointCrossoverOperator(Population *population, Population *selectedPopulation) {
  int i;

  /* We can't crossover without at least two individuals */
  if (selectedPopulation->size > 1) {
    for (i = 0; i < selectedPopulation->size - 1; i += 2)
      if (randf() < config.crossoverProb)  
	onepointCrossover(selectedPopulation->inds[i]->genotype, selectedPopulation->inds[i+1]->genotype);

    if (selectedPopulation->size % 2 == 1)
      if (randf() < config.crossoverProb)
	onepointCrossover(selectedPopulation->inds[i]->genotype, selectedPopulation->inds[randnSafe(i)]->genotype);
  }
  return selectedPopulation;
}
