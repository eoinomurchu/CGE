#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "confuse.h"

#include "genotype.h"
#include "genops.h"
#include "initialisation.h"

cfg_t *config;

void readConfigFile() {
  cfg_opt_t opts[] =
    {
      CFG_INT("populationSize", 10, CFGF_NONE),
      CFG_INT("maxInitialSize", 100, CFGF_NONE),
      CFG_STR("initialisation", "random", CFGF_NONE),
      CFG_STR("mutation", "intflip", CFGF_NONE),
      CFG_INT("mutationRate", 1, CFGF_NONE),
      CFG_STR("crossover", "onepoint", CFGF_NONE),
      CFG_FLOAT("crossoverProb", 0.9f, CFGF_NONE),
      CFG_END()
    };
  
  config = cfg_init(opts, CFGF_NONE);
  if(cfg_parse(config, "cge.conf") == CFG_PARSE_ERROR)
    printf("Unable to read cge.conf. Assuming defaults\n");
}

void getInitialiser() {
  const char *random = "random";

  if (strcmp(cfg_getstr(config, "initialisation"), random) == 0)
    initialise = randomInitialisation;
}

void getMutationOp() {
  const char *intflip = "intflip";

  if (strcmp(cfg_getstr(config, "mutation"), intflip) == 0)
    mutate = intflipMutation;
}

void getCrossoverOp() {
  const char *onepoint = "onepoint";

  if (strcmp(cfg_getstr(config, "crossover"), onepoint) == 0)
    crossover = onepointCrossover;
}

int main(int argc, char **argv) {
 
  srand(1);

  readConfigFile();
  getInitialiser();
  getMutationOp();
  getCrossoverOp();

  int populationSize = cfg_getint(config, "populationSize");

  Genotype **genotypes = createGenotypes(populationSize);
  initialise(genotypes, populationSize);
  
  int i,j;
  for (i = 0; i < populationSize; i++)
    for (j = 0; j < genotypes[i]->length; j++)
      printf("%p: %d\n", genotypes[i], genotypes[i]->codons[j]);

  mutate(genotypes[0]);
  for (i = 0; i < populationSize; i++)
    for (j = 0; j < genotypes[i]->length; j++)
      printf("%p: %d\n", genotypes[i], genotypes[i]->codons[j]);

  cfg_free(config);
  return 0;
}
