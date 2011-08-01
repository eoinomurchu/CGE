#ifndef CONFIG_H
#define CONFIG_H

/* Holds the config/params */
typedef struct {
  int seed;
  char *grammarFile;

  unsigned int generations;
  unsigned int populationSize;

  char *initialisation;
  unsigned int maxInitialSize;

  char *mutation;
  unsigned int mutationRate;

  char *crossover;
  float crossoverProb;
} Config;

/* Program wide parameters */
extern Config config;

/* Get the parameters from the command line */
void getOpts(int, char **);

/* Set the seed for rand */
void setSeed();

/* Set the initialisation method/functor */
void setInitialiser();

/* Set the mutation operation/functor */
void setMutationOp();

/* Set the crossover operation/functor */
void setCrossoverOp();

#endif
