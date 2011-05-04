
#ifndef INCLUDED_DIP_INVERT_IMAGE_FF_H
#define INCLUDED_DIP_INVERT_IMAGE_FF_H

#include <gr_block.h>

class dip_invert_image_ff;

 
typedef boost::shared_ptr<dip_invert_image_ff> dip_invert_image_ff_sptr;

 
dip_invert_image_ff_sptr dip_make_invert_image_ff ();

 
class dip_invert_image_ff : public gr_block
{
private:
 
  friend dip_invert_image_ff_sptr dip_make_invert_image_ff ();

  dip_invert_image_ff ();  	// private constructor

 public:
  ~dip_invert_image_ff();	// public destructor

 
 int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif 
