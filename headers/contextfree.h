#ifndef CONTEXTFREE_H
#define CONTEXTFREE_H

#include "grammar.h"

/* Read in a context-free gramar */
Grammar *readContextFreeGrammar();

/*
 * Prints out the CFG in BNF
 */
void printCFG();

/* 
 * Map an individual using a CFG 
 * 1 - success
 * 0 - failed
 */
int mapCFG(Individual *);

#endif
