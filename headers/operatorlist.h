#ifndef OPERATORLIST_H
#define OPERATORLIST_H

/* 
 * List of available operators for use in the pipeline.  The strings
 * here will be compared to the operator strings passed in and used to
 * asssign the correct operator functors to the pipeline.
 */

/* Initialisation */
static const char *op_random = "random";

/* Selection */
static const char *op_tournament = "tournament";

/* Genetic Ops */
static const char *op_onepoint = "onepoint";
static const char *op_intflip = "intflip";

#endif
