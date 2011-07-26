#ifndef GENOTYPE_H
#define GENOTYPE_H

/* Genotype/Chromosome */
typedef struct genotype {
  unsigned int *codons;
  unsigned char **mappedSymbols;
  unsigned int length;
  unsigned int maxLength;
  unsigned int encodingLength;
} Genotype;

#endif
