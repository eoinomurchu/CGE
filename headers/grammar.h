#ifndef GRAMMAR_H
#define GRAMMAR_H

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

extern Grammar *grammar;
#endif
