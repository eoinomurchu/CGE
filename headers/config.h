#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
  unsigned int generations;
  unsigned int populationSize;

  char *initialisation;
  unsigned int maxInitialSize;

  char *mutation;
  unsigned int mutationRate;

  char *crossover;
  float crossoverProb;
} Config;

extern Config config;

void getOpts(int, char **);

#endif
