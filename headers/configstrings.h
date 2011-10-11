#ifndef CONFIGSTRINGS_H
#define CONFIGSTRINGS_H

/* List of available fitness functions */
static const char *ff_sextic = "sextic";

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
