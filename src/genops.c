#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "genops.h"
#include "util.h"

/*
 * Operation
 */
static void intflipMutation(Genotype *individual) {
  int i; 
  for (i = 0; i < config.mutationRate; i++)
    individual->codons[randn(individual->length)] = rand();
}

/*
 * Operator Functor
 */
void intflipMutationOperator(Population *population) {

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
void onepointCrossoverOperator(Population *population) {

}
