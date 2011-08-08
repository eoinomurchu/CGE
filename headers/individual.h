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
} Individual;  

typedef struct {
  Individual **inds;
  unsigned int size;
} Population;

#endif
