#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util.h"
#include "config.h"
#include "individual.h"
#include "genops.h"
#include "initialisation.h"

/* The parameters/config */
Config config;

int main(int argc, char **argv) {
 
  getOpts(argc, argv);

  Genotype **genotypes = createGenotypes(config.populationSize);
  initialise(genotypes, config.populationSize);
  
  int i,j;
  for (i = 0; i < config.populationSize; i++) {
    for (j = 0; j < genotypes[i]->length; j++)
      printf(" %d", genotypes[i]->codons[j]);
    printf("\n");
  }

  crossover(genotypes[0], genotypes[1]);
  for (i = 0; i < config.populationSize; i++) {
    for (j = 0; j < genotypes[i]->length; j++)
      printf(" %d", genotypes[i]->codons[j]);
    printf("\n");
  }

  return 0;
}
