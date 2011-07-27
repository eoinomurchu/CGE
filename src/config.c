#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "genops.h"
#include "initialisation.h"

void setInitialiser() {
  char *random = "random";
  
  if (strcmp(config.initialisation, random) == 0)
    initialise = randomInitialisation;
}

void setMutationOp() {
  char *intflip = "intflip";
  
  if (strcmp(config.mutation, intflip) == 0)
    mutate = intflipMutation;
}

void setCrossoverOp() {
  char *onepoint = "onepoint";
  
  if (strcmp(config.crossover, onepoint) == 0)
    crossover = onepointCrossover;
}

/* Get the parameters from the command line */
void getOpts(int argc, char **argv) {
  int c;
  while ((c = getopt (argc, argv, "G:P:I:i:M:m:C:c:")) != -1) {
    printf("Option: %c\n", optopt); 
    printf("Option pointer: %p\n", optarg); 
    switch (c) {
      case 'G': 
        config.generations = atoi(optarg);
        break;
      case 'P':
        config.populationSize = atoi(optarg);
        break;
      case 'I':
        config.initialisation = optarg;
        setInitialiser();
        break;
      case 'i':
        config.maxInitialSize = atoi(optarg);
        break;
      case 'M':
        config.mutation = optarg;
        setMutationOp();
        break;
      case 'm':
        config.mutationRate = atoi(optarg);
        break;
      case 'C':
        config.crossover = optarg;
        setCrossoverOp();
        break;
      case 'c':
        config.crossoverProb = atof(optarg);
        break;
      default:
        printf("unknown option: '%c'\n", optopt); 
    }
  }
}
