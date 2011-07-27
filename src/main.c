#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "config.h"
#include "individual.h"
#include "genops.h"
#include "initialisation.h"

/* The parameters/config */
Config config = {
  -1,          /* Seed, -1 == time(NULL) */
  200,         /* Generations */
  50,          /* Population Size */
  "random",    /* Initialisation */
  100,         /* Initial Max Size */
  "intflip",   /* Mutation Op */
  1,           /* Mutation Rate - Ops per individual */
  "onepoint",  /* Crossover Op */
  0.9f         /* Crossover Rate */
};;

int main(int argc, char **argv) {
 
  /* Parse any options on the command line */
  getOpts(argc, argv);

  /* Set rand seed */
  setSeed();

  /* Set operator functors */
  setInitialiser();
  setMutationOp();
  setCrossoverOp();

  /* Initialise the population */
  Population *population = createPopulation(config.populationSize);
  initialise(population, config.populationSize);

  /* Pipeline Loop */
  int g;
  for (g = 0; g < config.generations; g++) {
    /* mapping */
    /* evaluation */
    /* selection */
    /* ops */
    /* replacement*/
  }
  
  return 0;
}
