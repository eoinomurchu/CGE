#include <stdlib.h>

#include "config.h"
#include "population.h"
#include "tournamentselection.h"
#include "util.h"

void tournamentSelectionOperator() {
  if (!selectedPopulation) {
    selectedPopulation = malloc(sizeof(Population));
    selectedPopulation->inds = malloc(population->size*sizeof(Individual*));
  }
  selectedPopulation->size = 0;

  while (selectedPopulation->size < population->size) {
    int i;
    Individual *best = population->inds[randn(population->size)];
    for (i = 1; i < config.tournamentSize; i++) {
      Individual *curr = population->inds[randn(population->size)];
      if (curr->fitness < best->fitness)
        best = curr;
    }
    selectedPopulation->inds[selectedPopulation->size++] = copyIndividual(best);
  }
}
