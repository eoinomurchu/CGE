#include <stdbool.h>
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
  "tournament,onepoint,intflip", /* Pipeline, list of operators */
  50,         /* Generations */
  100,          /* Population Size */
  "random",    /* Initialisation */
  100,         /* Initial Max Size */
  2,          /* Tournament Size*/
  10,           /* Mutation Rate - Ops per individual */
  0.7,         /* Crossover Rate */
  "sextic", /* Problem */
  false /* Debug? */
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
  Individual *best;
  unsigned int i,g, o;

  /* Parse any options on the command line */
  getOpts(argc, argv);

  /* Set rand seed */
  setSeed();

  /* Set initialisation */
  setInitialiser();

  /* Set operator functors */
  setPipeline();

  /* Set the fitness function */
  setFitnessFunction();

  /* Only one mapper so far */
  map = mapCFG;

  readGrammar = readContextFreeGrammar;
  grammar = readGrammar();

  /* Initialise the population */
  population = createPopulation(config.populationSize);
  initialise(population, config.populationSize);

  /* Initial mapping and evaluation */
  for (i = 0; i < population->size; i++) {
    population->inds[i]->valid = map(population->inds[i]);
    if (population->inds[i]->valid)
      evaluate(population->inds[i]);
    else
      population->inds[i]->fitness = DEFAULT_FITNESS;
  }

  /* Generation Loop */
  for (g = 0; g < config.generations+1; g++) {

    best = findBestIndiviual(population);
    printf("%6d: %10.5f %s\n", g, best->fitness, best->phenotype);
    best = NULL;

    /* Pipline loop */
    /* elite selection TODO */

    /* selection, genetic ops */
    selectedPopulation = population;

    for (o = 0; o < pipeline->count; o++)
      selectedPopulation = pipeline->ops[o](selectedPopulation);

    /* mapping and evaluation */
    for (i = 0; i < selectedPopulation->size; i++) {
      selectedPopulation->inds[i]->valid = map(selectedPopulation->inds[i]);
      if (selectedPopulation->inds[i]->valid)
	evaluate(selectedPopulation->inds[i]);
      else
	selectedPopulation->inds[i]->fitness = DEFAULT_FITNESS;
    }

    clearPopulation(population);
    population = selectedPopulation;
    selectedPopulation = NULL;

    /* replacement*/
    /* TODO */
  }

  clearPopulation(population);

  return 0;
}
