
include $(top_srcdir)/Makefile.common

AM_CPPFLAGS += -I$(top_srcdir)/lib

if PYTHON
###################################
# SWIG Python interface and library

TOP_SWIG_IFILES = \
	dip.i

# Install so that they end up available as:
#   import dip
# This ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/$(modname)

dip_la_swig_libadd =		\
	$(top_builddir)/lib/libgnuradio-dip.la

include $(top_srcdir)/Makefile.swig

# add some of the variables generated inside the Makefile.swig.gen
BUILT_SOURCES = $(swig_built_sources)

# Do not distribute the output of SWIG
no_dist_files = $(swig_built_sources)

# additional SWIG files to be installed
dip_swiginclude_headers = \
	dip_image_source.i \
	dip_image_sink.i \
	dip_invert_image_ff.i \
	dip_sub_image.i \
	dip_file_sink.i

endif
