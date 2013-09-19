#ifndef PIPELINE_H
#define PIPELINE_H

#include "population.h"

/* Struct for the pipeline, array of op functors */
typedef struct {
  Population *(**ops)(Population *, Population *);
  unsigned int count;
} Pipeline;

extern Pipeline *pipeline;

#endif
