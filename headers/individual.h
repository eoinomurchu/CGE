#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

/* Genotype/Chromosome */
typedef struct {
  unsigned int *codons;
  unsigned char **mappedSymbols;
  unsigned int length;
  unsigned int maxLength;
  unsigned int encodingLength;
} Genotype;

typedef char* Phenotype;

typedef struct {
  Genotype *genotype;
  Phenotype *phenotype;
} Individual;  

typedef struct {
  Individual **inds;
  unsigned int size;
} Population;

#endif
