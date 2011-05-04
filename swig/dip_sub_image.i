/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access dip_sub_image from python as dip.image_sink
 */
GR_SWIG_BLOCK_MAGIC(dip,sub_image);

dip_sub_image_sptr dip_make_sub_image (int height, int width, int depth, int channels,int x_coord,int y_coord, int height_sub, int width_sub);

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
};
