#ifndef GRAMMAR_H
#define GRAMMAR_H

typedef struct {
  char *startSymbol;
  char **productions;
  int count;
} Rule;

typedef struct {
  Rule *rules;
  int count;
} CFG;

typedef union {
  CFG cfg;
} Grammar;

/** Functor, Grammar returned can be either type */
Grammar *(*readGrammar)();

extern Grammar *grammar;
#endif
