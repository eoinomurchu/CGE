#ifndef PIPELINE_H
#define PIPELINE_H

#include "individual.h"

typedef struct {
  void (**ops)(Population *);
  unsigned int count;
} Pipeline;

extern Pipeline *pipeline;

#endif
