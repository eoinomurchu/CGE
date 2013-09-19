#ifndef UTIL_H
#define UTIL_H

/* Random number from (0, RAND_MAX] */
int randSafe();

/* Random number from [0, n) */
int randn(int n);

/* Random number from (0, n] */
int randnSafe(int n);

/* Random float from [0.0, 1.0] */
float randf();

/* Random double from [0.0, 1.0] */
double randd();

#endif
