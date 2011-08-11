#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "genops.h"
#include "initialisation.h"
#include "tournamentselection.h"
#include "pipeline.h"

/* 
 * Get the parameters from the command line
 */
void getOpts(int argc, char **argv) {
  int c;
  while ((c = getopt (argc, argv, "S:G:P:I:i:M:m:C:c:")) != -1) {
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
  char *random = "random";
  
  if (strcmp(config.initialisation, random) == 0)
    initialise = randomInitialisation;
}

/* 
 * Sets all of the operators in the pipeline by parsing the comma
 * seperated list and inserting the respective functors in to the
 * pipeline.
 */
void setPipeline() {;
  char *tournament = "tournament";
  char *onepoint = "onepoint";
  char *intflip = "intflip";

  pipeline = malloc(sizeof(Pipeline));
  pipeline->count = 0;

  int numberOfOperators = 1;
  char *c = config.operators;
  while (*c != '\0')
    if (*(c++) == ',')
      numberOfOperators++;
  
  pipeline->ops = malloc(numberOfOperators*sizeof(void (*)(Individual *)));

  /* Parse the opertors (comma seperated) */
  char *previous = config.operators;
  while (previous != NULL+1) {
    c = strchr(previous, ',');

    if (strncmp(previous, intflip, strlen(intflip)) == 0)
      pipeline->ops[pipeline->count++] = intflipMutationOperator;
    else if (strncmp(previous, onepoint, strlen(onepoint)) == 0)
      pipeline->ops[pipeline->count++] = onepointCrossoverOperator;
    else if (strncmp(previous, tournament, strlen(onepoint)) == 0)
      pipeline->ops[pipeline->count++] = tournamentSelectionOperator;

    previous = c + 1;
  }
}
