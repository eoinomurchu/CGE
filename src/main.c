#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "contextfree.h"
#include "fitnessfunction.h"
#include "genops.h"
#include "grammar.h"
#include "initialisation.h"
#include "pipeline.h"
#include "population.h"
#include "tree.h"
#include "util.h"

/* The parameters/config */
Config config = {
  -1,          /* Seed, -1 == time(NULL) */
  "grammars/default.bnf", /* Grammar File */
  "random,tournament,onepoint,intflip", /* Pipeline, list of operators */
  1,         /* Generations */
  2,          /* Population Size */
  "",    /* Initialisation */
  20,         /* Initial Max Size */
  1,          /* Tournament Size*/
  0,           /* Mutation Rate - Ops per individual */
  1.0f,         /* Crossover Rate */
  "sextic"
};

/* The grammar */
Grammar *grammar;

/* The main population */
Population *population;

/* The selected population */
Population *selectedPopulation;

/* The pipeline */
Pipeline *pipeline;

/*
 * Entry point
 */
int main(int argc, char **argv) {
  
  /* Parse any options on the command line */
  getOpts(argc, argv);

  /* Set rand seed */
  setSeed();

  /* Set operator functors */
  setPipeline();

  /* Set the fitness function */
  setFitnessFunction();

  readGrammar = readContextFreeGrammar;
  grammar = readGrammar();

  /* Initialise the population */
  population = createPopulation(config.populationSize);
  initialise(population, config.populationSize);

  /* Only one mapper so far */
  map = mapCFG;

  /* Initial mapping and evalution */
  int i;
  for (i = 0; i < population->size; i++) {
    population->inds[i]->valid = map(population->inds[i]);
    /* evaluation here */
  }

  /* Generation Loop */
  int g;
  for (g = 0; g < config.generations; g++) {

    /* Pipline loop */
    /* selection, genetic ops */
    int o;
    for (o = 0; o < pipeline->count; o++)
      pipeline->ops[o]();

    clearPopulation(population);
    population = selectedPopulation;

    /* mapping and evaluation */
    int i;
    for (i = 0; i < population->size; i++) {
      population->inds[i]->valid = map(population->inds[i]);
      evaluate(population->inds[i]);
    }

    /* replacement*/
    /* TODO */
  }
  
  return 0;
}
