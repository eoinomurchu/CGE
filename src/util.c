#include <stdlib.h>

#include "util.h"

/* Random number from (0, RAND_MAX] */
int randSafe() {
  return rand() + 1; 
}

/* Random number from [0, n] */
int randn(int n) {
  return rand() % n; 
}

/* Random number from (0, n] */
int randnSafe(int n) {
  return (rand() % n) + 1; 
}

/* Random float from [0.0, 1.0] */
float randf() {
  float f = (float)rand()/(float)RAND_MAX; 
  return f > 1.0f ? 1.0f : f;
}
