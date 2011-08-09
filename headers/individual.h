#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

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

Individual *copyIndividual(Individual *);

Population *copyPopulation(Population*);

#endif
