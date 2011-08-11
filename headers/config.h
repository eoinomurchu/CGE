#ifndef CONFIG_H
#define CONFIG_H

/* Holds the config/params */
typedef struct {
  int seed;
  char *grammarFile;
  char *operators;
  unsigned int generations;
  unsigned int populationSize;
  char *initialisation;
  unsigned int maxInitialSize;
  unsigned int tournamentSize;
  unsigned int mutationRate;
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

/* */
void setPipeline();

#endif
