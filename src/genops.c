#include <stdlib.h>
#include <string.h>

#include "confuse.h"

#include "genops.h"
#include "initialisation.h"

extern cfg_t *config;

void intflipMutation(Genotype *individual) {
  int i; 
  for (i = 0; i < cfg_getint(config, "mutationRate"); i++)
    individual->codons[rand()%individual->length] = rand();
}

void onepointCrossover(Genotype *parent, Genotype *spouse) {
  /* Only crossover with a certain probability */
  if ((float)rand()/(float)RAND_MAX > cfg_getfloat(config, "crossoverProb"))
    return;

  /* Get xo points - TODO get points from inside encoding region */
  int parentPoint = rand()%parent->length;
  int spousePoint = rand()%spouse->length;

  int parentLength = parent->length - parentPoint;
  int spouseLength = spouse->length - spousePoint;

  /* Increase chromosome capacity if required */
  if (parentPoint +  spouseLength > parent->maxLength) {
    parent->maxLength = parentPoint + spouseLength;
    realloc(parent->codons, parent->maxLength*sizeof(unsigned int));
  }
  if (spousePoint + parentLength > spouse->maxLength) {
    spouse->maxLength = spousePoint + parentLength;
    realloc(spouse->codons, spouse->maxLength*sizeof(unsigned int));
  }

  /* Simple temp buffer copying */
  unsigned int *temp;
  memcpy(temp, (parent->codons + parentPoint), parentLength*sizeof(unsigned int));
  memcpy((parent->codons + parentPoint), (spouse->codons + spousePoint), spouseLength*sizeof(unsigned int));
  memcpy((spouse->codons + spousePoint), temp, parentLength*sizeof(unsigned int));
}
