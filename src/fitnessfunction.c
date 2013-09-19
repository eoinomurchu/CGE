#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fitnessfunction.h"
#include "util.h"

static void malformedCode(const char *string) {
  fprintf(stderr, "Malformed Phenotype. The following code was malformed and could not be evalutated: ");
  fprintf(stderr,string);
  fprintf(stderr,"\n");
  exit(EXIT_FAILURE);
}

/**
 *
 */
double rpnInterpreter(const char *expr, const double *inputs, const int numberOfInputs) {
  double stack[2048];
  int pc = 0;
  double *sp = stack - 1;

  while (pc < strlen(expr) && (sp >= stack-1 && sp < (stack+2048))) {
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
  //printf("Top of stack (%ld) for input %f: %20.19f %s\n", sp-stack, inputs[0], *sp, expr);
  return *sp;
}

double **generateTrainingCases(const char *target, const Range *range) {
  double *d, *d2;
  int i;
  double size, input[1];
  double **cases = malloc(range->step * sizeof(double *));
  cases[0] = malloc(2 * range->step * sizeof(double));

  /*  printf("Pointers are at %X, %X,...%X\n", &cases[0], &cases[1],&cases[((int)range->step)-1]);
  printf("Data is from %X to %X\n", cases[0], (cases[0] + (int)(2 * range->step * sizeof(double))));
  printf("Doubles are %X\n", sizeof(double));
  printf("Double pointers are %X\n", sizeof(double*));

  d = 0;
  d2 = d + 2;

  printf("Double pointer plus two: %X -> %X\n", d, d2);*/

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
