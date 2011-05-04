
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <dip_invert_image_ff.h>
#include <gr_io_signature.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string.h>


dip_invert_image_ff_sptr 
dip_make_invert_image_ff ()
{
  return dip_invert_image_ff_sptr (new dip_invert_image_ff ());
}

/*
 * Specify constraints on number of input and output streams.
 * This info is used to construct the input and output signatures
 * (2nd & 3rd args to gr_block's constructor).  The input and
 * output signatures are used by the runtime system to
 * check that a valid number and type of inputs and outputs
 * are connected to this block.  In this case, we accept
 * only 1 input and 1 output.
 */
static const int MIN_IN = 1;	// mininum number of input streams
static const int MAX_IN = 1;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

/*
 * The private constructor
 */
dip_invert_image_ff::dip_invert_image_ff()
  : gr_block ("invert_image_ff",
		   gr_make_io_signature (MIN_IN, MAX_IN, sizeof(float)),
		   gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof (float)))
{
  	
}

/*
 * Our virtual destructor.
 */
dip_invert_image_ff::~dip_invert_image_ff ()
{
  // nothing else required in this example
}

int 
dip_invert_image_ff::general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items)
{
  float *in = (float *) input_items[0];
  float *o = (float *) output_items[0];
  int i,j,k;
  int size = noutput_items;
  
  for(i=0;i<size;i++)
   {	
	o[i]=255-in[i];
    }
	

  consume_each(noutput_items);
  return noutput_items;
}
