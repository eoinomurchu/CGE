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
#include "tree.h"
#include "util.h"

/* The parameters/config */
Config config = {
  -1,          /* Seed, -1 == time(NULL) */
  "grammars/default.bnf", /* Grammar File */
  "intflip,onepoint", /* Pipeline, list of operators */
  1,         /* Generations */
  5,          /* Population Size */
  "random",    /* Initialisation */
  20,         /* Initial Max Size */
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
  grammar = readGrammar();

  /* Initialise the population */
  Population *population = createPopulation(config.populationSize);
  initialise(population, config.populationSize);

  map = mapCFG;
  int i;
  for (i = 0; i < population->size; i++) {
    if (map(population->inds[i]))
      printf("%s\n",population->inds[i]->phenotype);
  }

  /* Generation Loop */
  int g;
  for (g = 0; g < config.generations; g++) {

    /* Pipline loop */

    /* mapping */
    int i;
    for (i = 0; i < population->size; i++)
      map(population->inds[i]);

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
