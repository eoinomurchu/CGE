#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "contextfree.h"
#include "genops.h"
#include "grammar.h"
#include "individual.h"
#include "initialisation.h"
#include "pipeline.h"
#include "util.h"

/* The parameters/config */
Config config = {
  -1,          /* Seed, -1 == time(NULL) */
  "grammars/default.bnf", /* Grammar File */
  "intflip,onepoint", /* Pipeline, list of operators */
  200,         /* Generations */
  50,          /* Population Size */
  "random",    /* Initialisation */
  100,         /* Initial Max Size */
  1,           /* Mutation Rate - Ops per individual */
  0.9f         /* Crossover Rate */
};

/* The grammar */
Grammar *grammar;

/* The pipeline */
Pipeline *pipeline;

int main(int argc, char **argv) {
 
  /* Parse any options on the command line */
  getOpts(argc, argv);

  /* Set rand seed */
  setSeed();

  /* Set operator functors */
  setInitialiser();
  setPipeline();

  readGrammar = readContextFreeGrammar;
  readGrammar();

  /* Initialise the population */
  Population *population = createPopulation(config.populationSize);
  initialise(population, config.populationSize);

  /* Generation Loop */
  int g;
  for (g = 0; g < config.generations; g++) {

    /* Pipline loop */
    /* mapping */
    /* evaluation */
    /* selection */
    /* ops */
    /* replacement*/
    int o;
    for (o = 0; o < pipeline->count; o++)
      pipeline->ops[o](population);
  }
  
  return 0;
}
