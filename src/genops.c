#include <stdlib.h>

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
  if ((float)rand()/(float)RAND_MAX > cfg_getfloat(config, "crossoverProb"))
    return;

  int parentPoint = rand()%parent->length;
  int spousePoint = rand()%spouse->length;

  if (parentPoint + (spouse->length-spousePoint) > parentPoint->maxLength) {
    parent->maxLength = parentPoint + (spouse->length-spousePoint);
    realloc(parent->codons, parent->maxLength*sizeof(unsigned int));
  }
  if (spousePoint + (parent->length-parentPoint) > spousePoint->maxLength) {
    spouse->maxLength = spousePoint + (parent->length-parentPoint);
    realloc(spouse->codons, spouse->maxLength*sizeof(unsigned int));
  }
}
