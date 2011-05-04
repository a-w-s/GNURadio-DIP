/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access dip_image_sink from python as dip.image_sink
 */
GR_SWIG_BLOCK_MAGIC(dip,image_sink);

dip_image_sink_sptr dip_make_image_sink (int height, int width, int depth, int channels);

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
};
