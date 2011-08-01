#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "contextfree.h"

/* Displays error message and quits */
static void malformedGrammar(char *string) {
  perror("Malformed Grammar Exception. The following string was malformed: ");
  perror(string);
  exit(EXIT_FAILURE);  
}

/* Creates a new empty rule in the grammar */
static Rule *addNewRule(CFG *grammar) {
  /* Too myny rules ? */
  if (grammar->count == (grammar->maxSize-1)) {
    grammar->maxSize *= 2;
    grammar->rules = realloc(grammar->rules, grammar->maxSize*sizeof(Rule*));
  }

  Rule *r = malloc(sizeof(Rule));
  r->count = 0;
  r->maxSize = 2;
  r->productions = malloc(grammar->maxSize*sizeof(Production*));
  
  grammar->rules[grammar->count++] = r;
  
  return r;
}

/* Creates a new empty production in the rule */
static Production *addNewProduction(Rule *r) {
  /* Too many productions? */
  if (r->count == (r->maxSize-1)) {
    r->maxSize *= 2;
    r->productions = realloc(r->productions, r->maxSize*sizeof(Production*));
  }
  
  /* New production */
  Production *p = malloc(sizeof(Production));
  p->count = 0;
  p->maxSize = 2;
  p->symbols = malloc(p->maxSize*sizeof(char*));

  r->productions[r->count++] = p;
  
  return p;
}

/* Adds a new symbol to the production */
static void addNewSymbol(Production *p, char *symbol) {
  /* Too many symbols? */
  if (p->count == (p->maxSize-1)) {
    p->maxSize *= 2;
    p->symbols = realloc(p->symbols, p->maxSize*sizeof(char*));
  }
  
  /* New symbol */
  p->symbols[p->count++] = symbol;
}

/* Reads a bnf grammar from a file */
Grammar *readContextFreeGrammar() {
  Grammar *grammar = malloc(sizeof(Grammar));
  CFG *cfg = (CFG *)grammar;

  cfg->count = 0;
  cfg->maxSize = 2;
  cfg->rules = malloc(cfg->maxSize*sizeof(Rule*));

  FILE *file = fopen(config.grammarFile, "r");
  
  if (file == NULL) {
    perror("Problem opening grammar file");
    exit(EXIT_FAILURE);
  }
  
  char line[1024];
  char *token, *previous,*symbol;
  char ntstart = '<';
  char ntend   = '>';
  char ruleDelim = '=';
  char productionDelim = '|';
  int maxLineLength = 1024;  
  int length;

  /* Rules */
  while (fgets(line, maxLineLength, file)) {
    if (line[0] != ntstart)
      malformedGrammar(line);

    /* Remove new line chars */
    int lineLength = strlen(line);
    if (line[lineLength - 1] == '\n') {
      line[lineLength - 1] = '\0';
      if (lineLength > 1 && line[lineLength - 2] == '\r')
        line[lineLength - 2] = '\0';
    }

    /* New rule */
    Rule *r = addNewRule(cfg);
    
    /* LHS Symbol */
    previous = line;
    token = strchr(line, ntend);
    length = 1 + token - previous;
    r->symbol = malloc((length+1)*sizeof(char));
    memcpy(r->symbol, line, length*sizeof(char));
    r->symbol[length] = '\0';
    previous = token;

    /* Productions - While the end of the line hasn't been reached */
    previous = strchr(line, ruleDelim) + 1;
    while (previous < line+lineLength) {
      /* Find the end of the current production */
      token = strchr(previous, productionDelim);
      char *end = token == NULL ? line+lineLength : token;

      /* New Produciton */
      Production *p = addNewProduction(r);

      /* Continue until there are no nt symbols left to process or we have entered the next production */
      token = strchr(previous, ntstart);
      while (token != NULL && token < end) {
        /* If there are preceeding terminal symbols, process them first */
        length = token - previous;
        if (length != 0) {
          symbol = malloc((length+1)*sizeof(char));
          memcpy(symbol, previous, length*sizeof(char));
          symbol[length] = '\0';
          addNewSymbol(p, symbol);
        }
        
        /* Process the actual nt symbol */
        previous = token;
        token = strchr(previous, ntend)+1;
        length = token - previous;

        symbol = malloc((length+1)*sizeof(char));
        memcpy(symbol, previous, length*sizeof(char));
        symbol[length] = '\0';
        addNewSymbol(p, symbol);

        /* Try find the next nt symbol */
        previous = token;
        token = strchr(previous, ntstart);
      }
      /* Loop is finished, no nt symbols remaining in this production */
      length = end - previous;
      
      /* Are there t symbols left? */
      if (length != 0) {
        symbol = malloc((length+1)*sizeof(char));
        memcpy(symbol, previous, length*sizeof(char));
        symbol[length] = '\0';
        addNewSymbol(p, symbol);
      }
      
      /* Move past the end of this production */
      previous = end+1;
    }
  }    

  return grammar;
}
