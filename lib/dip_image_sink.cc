#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include<dip_image_sink.h>
#include<gr_io_signature.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdexcept>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;

dip_image_sink_sptr
dip_make_image_sink (int height, int width, int depth, int channels)
{
	return dip_image_sink_sptr (new dip_image_sink(height, width, depth, channels));
}

dip_image_sink::dip_image_sink (int height, int width, int depth, int channels)
	: gr_block ("image_sink",
			gr_make_io_signature (1, 1, sizeof(float)),
			gr_make_io_signature (0,0,0)),d_flag(0),d_height(0),d_width(-1),d_channels(0)
{ 	
 	d_img=cvCreateImage(cvSize(width,height),depth,channels);
}

dip_image_sink::~dip_image_sink ()
{
	cvReleaseImage(&d_img);
}

int 
dip_image_sink::general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items)
{

	float *in = (float *) input_items[0];		
	int i,j,k=0,z;
  	int size = noutput_items;
	CvScalar s;	
	int channels=d_img->nChannels,height=d_img->height,width=d_img->width;
 		
	if(d_flag==0)
	{
		cout<<"Building Image ";		
	}
	
	d_flag=1;

	i=d_height;
	j=d_width;
	z=d_channels;

	while(k!=size)
	{				
		if(i==(height-1) && j==(width-1) && z==channels)
		{	
			cout<<"100%"<<endl;					
			cvNamedWindow("Output Image", CV_WINDOW_AUTOSIZE); 
			cvMoveWindow("Output Image", 150, 150);
	 		cvShowImage("Output Image", d_img);
			cvWaitKey(0);	
			cvDestroyWindow("Output Image");
			break;
		}
		if(z==channels)z=0;
		if(d_flag==1)
		{
			cout<<"|";
			d_flag=2;
		}
				
		while(z<channels)
		{	
			if(k==size)
			{
				d_height=i;
				d_width=j;
				d_channels=z;
			  	consume_each(noutput_items);
				return noutput_items;
			}
			s.val[z++]=in[k++];			
		}

		if(j==(width-1))
		{
			j=-1;
			i++;
		}
		j++;
		cvSet2D(d_img,i,j,s);
	}	
	d_height=i;
	d_width=j;
	d_channels=z;

  	consume_each(noutput_items);
	return noutput_items;
}

