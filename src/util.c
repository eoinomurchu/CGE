#include <stdlib.h>

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
