#ifndef POPULATION_H
#define POPULATION_H

#include "tree.h"

/* Genotype/Chromosome */
typedef struct {
  unsigned int *codons;
  unsigned char **mappedSymbols;
  unsigned int length;
  unsigned int maxLength;
  unsigned int encodingLength;
} Genotype;

typedef char Phenotype;

typedef struct {
  Genotype *genotype;
  Phenotype *phenotype;
  Tree *derivationTree;
  int valid;
  float fitness;
} Individual;  

typedef struct {
  Individual **inds;
  unsigned int size;
} Population;

extern Population *population;

extern Population *selectedPopulation;

Individual *copyIndividual(Individual *);

Population *copyPopulation(Population *);

void clearPopulation(Population *);

void printPopulation(Population *);
#endif
