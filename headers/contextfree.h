#ifndef CONTEXTFREE_H
#define CONTEXTFREE_H

#include "grammar.h";

/* Read in a context-free gramar */
Grammar *readContextFreeGrammar();

/* Map an individual using a CFG */
void mapCFG(Individual *);

#endif
