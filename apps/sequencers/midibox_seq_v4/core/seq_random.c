// $Id$
/*
 * Random generator
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////

// initial seed
static unsigned int random_value = 0xdeadbabe;


/////////////////////////////////////////////////////////////////////////////
// random generator function
/////////////////////////////////////////////////////////////////////////////
u32 SEQ_RANDOM_Gen(u32 seed)
{
  if( seed )
    random_value = seed;

  // MEMO: for thread safeness, we would have to pass a pointer to random_value through the SEQ_RANDOM_Gen() function
  // however, multiple threads just increase the randomness even more - therefore this approach is fine ;-)

  // TODO: combine with timer values for even more randomness
  rand_r(&random_value);

  return random_value;
}


/////////////////////////////////////////////////////////////////////////////
// returns random number in a given range
/////////////////////////////////////////////////////////////////////////////
u32 SEQ_RANDOM_Gen_Range(u32 min, u32 max)
{
  // values equal? -> no random number required
  if( min == max )
    return min;

  // swap min/max if reversed
  if( min > max ) {
    u32 tmp;
    tmp = min;
    min = max;
    max = tmp;
  }

  // generate new random number
  rand_r(&random_value);

  // return result within the given range
  return min + (random_value % (max-min+1));
}