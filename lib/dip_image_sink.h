#ifndef INCLUDED_DIP_IMAGE_SINK_H
#define INCLUDED_DIP_IMAGE_SINK_H

#include<gr_block.h>
#include<cv.h>
#include<highgui.h>

class dip_image_sink;

typedef boost::shared_ptr<dip_image_sink> dip_image_sink_sptr;

dip_image_sink_sptr
dip_make_image_sink (int height, int width, int depth, int channels);

class dip_image_sink : public gr_block
{
	private:
	friend dip_image_sink_sptr dip_make_image_sink (int height, int width, int depth, int channels);		
	int d_height;
	int d_width;
	int d_channels;		
	int d_flag;
	IplImage* d_img; 
	dip_image_sink (int height, int width, int depth, int channels);
	
 	public: 
	~dip_image_sink ();

  	int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DIP_IMAGE_SINK_H */
