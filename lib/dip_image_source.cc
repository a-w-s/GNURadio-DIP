
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include<dip_image_source.h>
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
#include<sys/shm.h>
#include<sys/ipc.h>
using namespace std;
 
dip_image_source_sptr
dip_make_image_source (const char *filename)
{
	return dip_image_source_sptr (new dip_image_source(filename));
}

dip_image_source::dip_image_source (const char *filename)
	: gr_block ("image_source",
		gr_make_io_signature (0, 0, 0),
		gr_make_io_signature (1, 1, sizeof(float))),d_flag(0),d_height(0),d_width(-1),d_channels(0)
{	 	
	d_img =cvLoadImage(filename,-1);
	if(!d_img)
	{
		throw std::runtime_error ("Can't open image file");
	}
}

dip_image_source::~dip_image_source ()
{
	cvReleaseImage(&d_img);
}


int 
dip_image_source::general_work (int noutput_items,
			       gr_vector_int &ninput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
	float *o = (float *) output_items[0];	
	int i,j,k=0,z;	
  	int size = noutput_items;	
  	CvScalar s;
 
	int height    = d_img->height;
	int width     = d_img->width;
	int channels  = d_img->nChannels;
	int depth     = d_img->depth;

	if(d_flag==0)
	{
		cout<<"Height in pixels         - "<<height<<endl;
		cout<<"Width in pixels          - "<<width<<endl;
		cout<<"Bit Depth of pixels      - "<<depth<<endl;
		cout<<"Number of color Channels - "<<channels<<endl;
		d_flag=1;
	}
	
	i=d_height;	
	j=d_width;
	z=d_channels;

	while(k!=size)
	{			
		if(i==(height-1) && j==(width-1) && z==channels)
		{	
			break;			
		}	
		if(z==channels)z=0;			
		if(j==(width-1))
		{
			j=-1;
			i++;
		}		

		j++;
		s=cvGet2D(d_img,i,j);
		while(z<channels)
		{
			if(k==size)
			{
				d_height=i;
				d_width=j;
				d_channels=z;
				consume_each(noutput_items);	
				return (noutput_items);				
			}
			o[k++]=s.val[z++];
		}
	}
	
	d_height=i;
	d_width=j;
	d_channels=z;
 	
	consume_each(noutput_items);
	return noutput_items;
}

