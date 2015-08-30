#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "configstrings.h"
#include "fitnessfunction.h"
#include "genops.h"
#include "initialisation.h"
#include "tournamentselection.h"
#include "pipeline.h"

/*
 * Get the parameters from the command line
 */
void getOpts(int argc, char **argv) {
  int c;
  while ((c = getopt (argc, argv, "dS:G:P:I:i:M:m:C:c:")) != -1) {
    /* printf("Option: %c\n", optopt);
       printf("Option pointer: %s\n", optarg); */
    switch (c) {
      case 'S':
        config.seed = atoi(optarg);
        break;
      case 'G':
        config.generations = atoi(optarg);
        break;
      case 'P':
        config.populationSize = atoi(optarg);
        break;
      case 'I':
        config.initialisation = optarg;
        break;
      case 'i':
        config.maxInitialSize = atoi(optarg);
        break;
      case 'm':
        config.mutationRate = atoi(optarg);
        break;
      case 'c':
        config.crossoverProb = atof(optarg);
        break;
      case 'O':
        config.operators = optarg;
        break;
      case 'd':
	config.debug = true;
	break;
      default:
        printf("unknown option: '%c'\n", optopt);
    }
  }
}

/*
 * Set the seed for rand
 */
void setSeed() {
  if (config.seed == -1)
    config.seed = time(NULL);

  srand(config.seed);
}

/*
 * Set the initialisation method/functor
 */
void setInitialiser() {
  if (strncmp(config.initialisation, op_random, strlen(op_random)) == 0)
    initialise = randomInitialisation;
}

/*
 * Set the fitness function
 */
void setFitnessFunction() {
  if (strncmp(config.fitnessfunction, ff_sextic, strlen(ff_sextic)) == 0)
    evaluate = sexticFitnessFunction;
}

/*
 * Sets all of the operators in the pipeline by parsing the comma
 * seperated list and inserting the respective functors in to the
 * pipeline.
 */
void setPipeline() {
  int numberOfOperators;
  char *c, *previous;

  pipeline = malloc(sizeof(Pipeline));
  pipeline->count = 0;

  numberOfOperators = 1;
  c = config.operators;
  while (*c != '\0')
    if (*(c++) == ',')
      numberOfOperators++;

  pipeline->ops = malloc(numberOfOperators*sizeof(void (*)(Population *)));

  /* Parse the opertors (comma seperated) */
  previous = config.operators;

  /* Grab the initialiser */
  c = strchr(previous, ',');
  config.initialisation = previous;
  setInitialiser();

  while (previous != (char *)NULL+1) {
    c = strchr(previous, ',');

    if (strncmp(previous, op_intflip, strlen(op_intflip)) == 0)
      pipeline->ops[pipeline->count++] = intflipMutationOperator;
    else if (strncmp(previous, op_onepoint, strlen(op_onepoint)) == 0)
      pipeline->ops[pipeline->count++] = onepointCrossoverOperator;
    else if (strncmp(previous, op_tournament, strlen(op_onepoint)) == 0)
      pipeline->ops[pipeline->count++] = tournamentSelectionOperator;

    previous = c + 1;
  }
}
