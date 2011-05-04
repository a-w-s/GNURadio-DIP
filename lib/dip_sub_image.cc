#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include<dip_sub_image.h>
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

dip_sub_image_sptr
dip_make_sub_image (int height, int width, int depth, int channels,int x_coord,int y_coord, int height_sub, int width_sub)
{
	return dip_sub_image_sptr (new dip_sub_image(height, width, depth, channels,x_coord,y_coord,height_sub,width_sub));
}

dip_sub_image::dip_sub_image (int height, int width, int depth, int channels,int x_coord,int y_coord, int height_sub, int width_sub)
	: gr_block ("sub_image",
			gr_make_io_signature (1, 1, sizeof(float)),
			gr_make_io_signature (0,0,0)),d_flag(0),d_height(0),d_width(-1),d_channels(0)
{ 	
 	d_img=cvCreateImage(cvSize(width,height),depth,channels);
	rect.x=x_coord;
	rect.y=y_coord;
	rect.height=height_sub;
	rect.width=width_sub;
	
}

dip_sub_image::~dip_sub_image ()
{
	cvReleaseImage(&d_img);
}

int 
dip_sub_image::general_work (int noutput_items,
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
			cvMoveWindow("Output Image", 100, 100);
			cvShowImage("Output Image", d_img );
			cvSetImageROI(d_img,rect);
			cvNamedWindow("Sub Image", CV_WINDOW_AUTOSIZE); 
			cvMoveWindow("Sub Image", 500, 100);
			cvShowImage("Sub Image", d_img );
			cvWaitKey(0);
			cvDestroyWindow("Sub Image");
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

