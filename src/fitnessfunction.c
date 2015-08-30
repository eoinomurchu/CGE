#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fitnessfunction.h"
#include "util.h"

static void malformedCode(const char *string) {
  fprintf(stderr, "Malformed Phenotype. The following code was malformed and could not be evalutated: %s\n", string);
  exit(EXIT_FAILURE);
}

/**
 *
 */
double rpnInterpreter(const char *expr, const double *inputs, const int numberOfInputs) {
  double stack[4096];
  int pc = 0;
  double *sp = stack - 1;

  while (pc < strlen(expr) && (sp >= stack-1 && sp < (stack+4096))) {
    char c = expr[pc++];

    switch(c) {
    case ' ':
    case '(':
    case ')': break;
    case '+': *(sp - 1) = *sp + *(sp - 1); --sp; break;
    case '-': *(sp - 1) = *sp - *(sp - 1); --sp; break;
    case '*': *(sp - 1) = *sp * *(sp - 1); --sp; break;
    case '/': *(sp - 1) = *sp / *(sp - 1); --sp; break;
    case 'x': c = expr[pc++]; *(++sp) = inputs[c-48]; break;
    case '1': *(++sp) = 1.0; break;
    default: malformedCode(expr);
    }
  }

  return *sp;
}

double **generateTrainingCases(const char *target, const Range *range) {
  int i;
  double size, input[1];
  double **cases = malloc(range->step * sizeof(double *));
  cases[0] = malloc(2 * range->step * sizeof(double));

  size = range->max - range->min;
  for (i = 0; i < range->step; i++) {
    if (i>0)
      cases[i] = cases[i-1] + 2;

    cases[i][0] = randd()*size + range->min;
    input[0] = cases[i][0];

    cases[i][1] = rpnInterpreter(target, input, 1);
  }

  return cases;
}
