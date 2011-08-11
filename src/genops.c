#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "genops.h"
#include "util.h"

/*
 * Operator/Operation function
 */
void intflipMutationOperator() {
  int i, m;
  for (i = 0; i < selectedPopulation->size; i++)
    for (m = 0; m < config.mutationRate; m++)
      selectedPopulation->inds[i]->genotype->codons[randn(selectedPopulation->inds[i]->genotype->length)] = rand();
}

/*
 * Operation
 */
static void onepointCrossover(Genotype *parent, Genotype *spouse) {
  /* Only crossover with a certain probability */
  if (randf() > config.crossoverProb)
    return;

  /* Get xo points - TODO get points from inside encoding region */
  int parentPoint = randn(parent->length);
  int spousePoint = randn(spouse->length);

  int parentLength = parent->length - parentPoint;
  int spouseLength = spouse->length - spousePoint;

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
  unsigned int *temp = malloc(parentLength*sizeof(unsigned int));
  memcpy(temp, (parent->codons + parentPoint), parentLength*sizeof(unsigned int));
  memcpy((parent->codons + parentPoint), (spouse->codons + spousePoint), spouseLength*sizeof(unsigned int));
  memcpy((spouse->codons + spousePoint), temp, parentLength*sizeof(unsigned int));
  free(temp);

  /* Update length */
  parent->length -= (parentLength - spouseLength);
  spouse->length += (parentLength - spouseLength);
}

/*
 * Operator Functor
 */
void onepointCrossoverOperator() {
  if (selectedPopulation->size < 2)
    return;

  int i;
  for (i = 0; i < selectedPopulation->size - 1; i += 2)
    if (randf() < config.crossoverProb)  
      onepointCrossover(selectedPopulation->inds[i]->genotype, selectedPopulation->inds[i+1]->genotype);

  if (selectedPopulation->size % 2 == 1)
    if (randf() < config.crossoverProb)
      onepointCrossover(selectedPopulation->inds[i]->genotype, selectedPopulation->inds[randnSafe(i)]->genotype);
}
