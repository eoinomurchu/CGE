#ifndef POPULATION_H
#define POPULATION_H

#include <stdbool.h>

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
  _Bool valid;
  double fitness;
} Individual;  

typedef struct {
  Individual **inds;
  unsigned int size;
} Population;

Individual *copyIndividual(Individual *);

Population *copyPopulation(Population *);

void clearPopulation(Population *);

void printIndividual(Individual *);

void printPopulation(Population *);

Individual *findBestIndiviual(Population *);

#endif
