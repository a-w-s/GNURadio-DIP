/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access dip_file_sink from python as dip.file_sink
 */
GR_SWIG_BLOCK_MAGIC(dip,file_sink);

dip_file_sink_sptr dip_make_file_sink (int height, int width, int depth, int channels,char * filename);

class dip_file_sink : public gr_block
{
	private:
	friend dip_file_sink_sptr dip_make_file_sink (int height, int width, int depth, int channels,char * filename);		
	int d_height;
	int d_width;
	int d_channels;		
	int d_flag;
	char d_outFileName[100];
	IplImage* d_img; 
	
 	public: 
	~dip_file_sink ();
};
