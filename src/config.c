#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "genops.h"
#include "initialisation.h"

/* Get the parameters from the command line */
void getOpts(int argc, char **argv) {
  int c;
  while ((c = getopt (argc, argv, "S:G:P:I:i:M:m:C:c:")) != -1) {
    printf("Option: %c\n", optopt); 
    printf("Option pointer: %s\n", optarg); 
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
      case 'M':
        config.mutation = optarg;
        break;
      case 'm':
        config.mutationRate = atoi(optarg);
        break;
      case 'C':
        config.crossover = optarg;
        break;
      case 'c':
        config.crossoverProb = atof(optarg);
        break;
      default:
        printf("unknown option: '%c'\n", optopt); 
    }
  }
}


/* Set the seed for rand */
void setSeed() {
  if (config.seed == -1)
    config.seed = time(NULL);

  srand(config.seed);
}

/* Set the initialisation method/functor */
void setInitialiser() {
  char *random = "random";
  
  if (strcmp(config.initialisation, random) == 0)
    initialise = randomInitialisation;
}

/* Set the mutation operation/functor */
void setMutationOp() {
  char *intflip = "intflip";
  
  if (strcmp(config.mutation, intflip) == 0)
    mutate = intflipMutation;
}

/* Set the crossover operation/functor */
void setCrossoverOp() {
  char *onepoint = "onepoint";
  
  if (strcmp(config.crossover, onepoint) == 0)
    crossover = onepointCrossover;
}
