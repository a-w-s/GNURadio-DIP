#ifndef INCLUDED_DIP_SUB_IMAGE_H
#define INCLUDED_DIP_SUB_IMAGE_H

#include<gr_block.h>
#include<cv.h>
#include<highgui.h>

class dip_sub_image;

typedef boost::shared_ptr<dip_sub_image> dip_sub_image_sptr;

dip_sub_image_sptr
dip_make_sub_image (int height, int width, int depth, int channels,int x_coord,int y_coord, int height_sub, int width_sub);

class dip_sub_image : public gr_block
{
	private:
	friend dip_sub_image_sptr dip_make_sub_image (int height, int width, int depth, int channels,int x_coord,int y_coord, int height_sub, int width_sub);		
	int d_height;
	int d_width;
	int d_channels;		
	int d_flag;
	IplImage* d_img; 
	CvRect rect;	
	dip_sub_image (int height, int width, int depth, int channels,int x_coord,int y_coord, int height_sub, int width_sub);
	
 	public: 
	~dip_sub_image ();

  	int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_dip_sub_image_H */
