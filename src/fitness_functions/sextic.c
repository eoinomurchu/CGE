#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "fitnessfunction.h"

static const unsigned int cases = 20;
static const char *target = "x0 x0 x0 x0 * * * x0 x0 x0 x0 * * * + x0 x0 x0 x0 x0 x0 * * * * * - x0 x0 * +\0";
static const Range range = {-1,20,1};
static double **trainingCases = NULL;

/** 
 * Classic sextic regression problem
 * x^6 - 2x^4 + x^2, {x in [-1,1]}
 */
double sexticFitnessFunction(Individual *i) {
  int c;
  double fitness = 0.0, result; 

  if (!trainingCases)
    trainingCases = generateTrainingCases(target, &range);

  /*printf("%s\n",i->phenotype);*/
  for (c = 0; c < range.step; c++) {
    /*    printf("Training case %d: %f %f\n", c, trainingCases[c][0], trainingCases[c][1]);*/
    result = rpnInterpreter(i->phenotype, trainingCases[c], 1);
    /*printf("Result: %f\n", result);
    printf("Expected: %f\n", trainingCases[c][1]);
    printf("Error: %f\n", pow(trainingCases[c][1] - result, 2));*/
    fitness += pow(trainingCases[c][1] - result, 2);
    /*printf("fitness: %f\n", fitness);*/
  }

  return i->fitness = fitness;
}
