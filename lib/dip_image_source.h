
#ifndef INCLUDED_DIP_IMAGE_SOURCE_H
#define INCLUDED_DIP_IMAGE_SOURCE_H

#include<cv.h>
#include<highgui.h>
#include<gr_block.h>

class dip_image_source;

typedef boost::shared_ptr<dip_image_source> dip_image_source_sptr; 

dip_image_source_sptr
dip_make_image_source (const char *filename);

class dip_image_source : public gr_block
{
	private:
	friend dip_image_source_sptr dip_make_image_source (const char *filename);			
	IplImage* d_img;
	int d_flag;
	int d_height;
	int d_width;
	int d_channels;
	dip_image_source (const char *filename);

 	public:	
	~dip_image_source ();

  	int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

};


#endif /* INCLUDED_DIP_IMAGE_SOURCE_H */
