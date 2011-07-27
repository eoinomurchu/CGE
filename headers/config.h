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
  unsigned float crossoverProb;
} Config;

#endif
