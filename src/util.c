#include <stdlib.h>
#include <stdio.h>

#include "util.h"

/* Random integer from (0, RAND_MAX] */
int randSafe() {
  int r = rand() + 1; 
  return r < 1 ? RAND_MAX : r;
}

/* Random integer from [0, n) */
int randn(int n) {
  return rand() % n; 
}

/* Random integer from (0, n] */
int randnSafe(int n) {
  return (rand() % n) + 1; 
}

/* Random float from [0.0, 1.0] */
float randf() {
  float f = (float)rand()/(float)RAND_MAX; 
  return f > 1.0f ? 1.0f : f;
}

/* Random double from [0.0, 1.0] */
double randd() {
  double d = (double)rand()/(double)RAND_MAX; 
  return d > 1.0 ? 1.0 : d;
}

void *reallocOrFail(void *pointer, size_t size) {
  void *newPointer = realloc(pointer, size);
  if (!newPointer) {
    free(pointer);
    perror("realloc failed");
    exit(EXIT_FAILURE);
  }
  return newPointer;
}
