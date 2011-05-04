/* -*- c++ -*- */

%include "gnuradio.i"			// the common stuff

%{
#include "dip_image_source.h"
#include "dip_image_sink.h"
#include "dip_invert_image_ff.h"
#include "dip_file_sink.h"
#include "dip_sub_image.h"
%}

%include "dip_image_source.i"
%include "dip_image_sink.i"
%include "dip_invert_image_ff.i"
%include "dip_file_sink.i"
%include "dip_sub_image.i"

