#ifndef CONFIG_H
#define CONFIG_H

/* Struct for holding the config/params */
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
  double crossoverProb;
  char *fitnessfunction;
  _Bool debug;
} Config;

/* Program wide parameters */
extern Config config;

/* Get the parameters from the command line */
void getOpts(int, char **);

/* Set the seed for rand */
void setSeed();

/* Set the initialisation method/functor */
void setInitialiser();

/* Set the fitness function */
void setFitnessFunction();

/* Read the pipeline string and file the pipeline with the correct
   functors */
void setPipeline();

#endif
