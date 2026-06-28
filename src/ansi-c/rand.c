#include <stdlib.h>

/* Read this for more information on these functions:     */
/* https://www.man7.org/linux/man-pages/man3/rand.3.html  */

static unsigned int next = 1;

/** Simple LCG (Linear Congruential Generator) based random number generator.
 * Taken from POSIX.1-2001.
 * @returns Random number from 0 to 32767 (16-bit)
*/
int rand(void)
{
  next = next * 1103515245u + 12345u;
  return (unsigned int)(next/65536) % 32768;
}

/** Set random number generator seed 
 * @param seed Random seed
*/
void srand(unsigned int seed)
{
  next = seed;
}