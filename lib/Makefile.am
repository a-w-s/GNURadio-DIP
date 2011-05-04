
include $(top_srcdir)/Makefile.common

# list of programs run by "make check" and "make distcheck"
TESTS = test_all

# ----------------------------------------------------------------
# howto C++ library: libgnuradio-dip.so
# ----------------------------------------------------------------

# C/C++ headers get installed in ${prefix}/include/$(modname)
modinclude_HEADERS = \
	dip_image_source.h \
	dip_image_sink.h \
	dip_invert_image_ff.h \
	dip_file_sink.h \
	dip_sub_image.h

lib_LTLIBRARIES = libgnuradio-dip.la

libgnuradio_dip_la_SOURCES = \
	dip_image_source.cc \
	dip_image_sink.cc \
	dip_invert_image_ff.cc \
	dip_sub_image.cc \
	dip_file_sink.cc

libgnuradio_dip_la_LIBADD = \
	$(GNURADIO_CORE_LA)

libgnuradio_dip_la_LDFLAGS = $(NO_UNDEFINED) $(LTVERSIONFLAGS)

