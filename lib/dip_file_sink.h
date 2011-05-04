#ifndef INCLUDED_DIP_FILE_SINK_H
#define INCLUDED_DIP_FILE_SINK_H

#include<gr_block.h>
#include<cv.h>
#include<highgui.h>

class dip_file_sink;

typedef boost::shared_ptr<dip_file_sink> dip_file_sink_sptr;

dip_file_sink_sptr
dip_make_file_sink (int height, int width, int depth, int channels,char * filename);

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
		
	dip_file_sink (int height, int width, int depth, int channels,char * filename);
	
 	public: 
	~dip_file_sink ();

  	int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_dip_file_sink_H */
