#ifndef PIPELINE_H
#define PIPELINE_H

#include "population.h"

typedef struct {
  void (**ops)();
  unsigned int count;
} Pipeline;

extern Pipeline *pipeline;

#endif
