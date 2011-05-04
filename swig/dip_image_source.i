/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access dip_image_source from python as dip.image_source
 */
GR_SWIG_BLOCK_MAGIC(dip,image_source);

dip_image_source_sptr dip_make_image_source (const char *filename);

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
};
