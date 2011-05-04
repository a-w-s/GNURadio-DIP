#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include<dip_file_sink.h>
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

dip_file_sink_sptr
dip_make_file_sink (int height, int width, int depth, int channels,char * filename)
{
	return dip_file_sink_sptr (new dip_file_sink(height, width, depth, channels,filename));
}

dip_file_sink::dip_file_sink (int height, int width, int depth, int channels,char * filename)
	: gr_block ("file_sink",
			gr_make_io_signature (1, 1, sizeof(float)),
			gr_make_io_signature (0,0,0)),d_flag(0),d_height(0),d_width(-1),d_channels(0)
{ 	
 	d_img=cvCreateImage(cvSize(width,height),depth,channels);
	strcpy(d_outFileName,filename);
}

dip_file_sink::~dip_file_sink ()
{
	cvReleaseImage(&d_img);
}

int 
dip_file_sink::general_work (int noutput_items,
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
			 if(!cvSaveImage(d_outFileName,d_img))
			 { 
				cout<<"Could not save: %s\n"<<d_outFileName;
			 }
			cvWaitKey(0);		
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

