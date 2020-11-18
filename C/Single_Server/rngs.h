
/* -----------------------------------------------------------------------
 * Name            : rngs.h  (header file for the library file rngs.c)
 * Author          : Steve Park & Dave Geyer
 * Language        : ANSI C
 * Latest Revision : 09-22-98
 * -----------------------------------------------------------------------
 */


#ifndef RNGS_H_
#define RNGS_H_

double Random(void);
void   PlantSeeds(long x);
void   GetSeed(long *x);
void   PutSeed(long x);
void   SelectStream(int index);

#endif
