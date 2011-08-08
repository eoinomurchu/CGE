#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "individual.h"

typedef struct {
  char **symbols;
  unsigned int count;
  unsigned int maxSize; 
} Production;

typedef struct {
  char *symbol;
  Production **productions;
  unsigned int count;
  unsigned int maxSize;
} Rule;

typedef struct {
  Rule **rules;
  unsigned int count;
  unsigned int maxSize;
} CFG;

typedef union {
  CFG cfg;
} Grammar;

/** Functor, Grammar returned can be either type */
Grammar *(*readGrammar)();

/** Functor, Map an individual's genotype to a phenotype */
int (*map)(Individual *);

extern Grammar *grammar;
#endif
