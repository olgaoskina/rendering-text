
OBJS= \
	autofit.o \
	bdf.o \
	cff.o \
	pfr.o \
	pcf.o \
	sfnt.o \
	raster.o \
	pshinter.o \
	winfnt.o \
	truetype.o \
	type1.o \
	type42.o \
	psaux.o \
	psnames.o \
	type1cid.o \
	ftbase.o \
	ftbitmap.o \
	ftcache.o \
	ftdebug.o \
	ftgasp.o \
	ftglyph.o \
	ftgzip.o \
	ftinit.o \
	ftlzw.o \
	ftstroke.o \
	ftsystem.o \
	smooth.o \

STATIC_OBJS=$(OBJS:%.o=%.static.o)
DYNAMIC_OBJS=$(OBJS:%.o=%.dynamic.o)

INCS= -I. -Ifreetype

CC=gcc
CFLAGS=
CFLAGS_D=-c -shared -fPIC -lc

AR=ar
AR_FLAGS=rc
RANLIB=ranlib

NAME_LIB=libfreetype
STATIC_LIB=$(NAME_LIB).a
DYNAMIC_LIB=$(NAME_LIB).so

$(STATIC_LIB):$(STATIC_OBJS)
	$(AR) $(AR_FLAGS) $@ $(STATIC_OBJS)
	$(RANLIB) $@

%.static.o : %.c
	$(CC) $(INCS) $(CFLAGS) -c $< -o $@

#$(DYNAMIC_LIB):$(DYNAMIC_OBJS)
#	$(CC) -shared -o $@ $<
$(DYNAMIC_LIB):$(DYNAMIC_OBJS)
	$(LD) -shared -o $@ $(DYNAMIC_OBJS)

%.dynamic.o : %.c
	$(CC) $(INCS) $(CFLAGS_D) $< -o $@

clean: 
	rm -f $(STATIC_OBJS)
	rm -f $(DYNAMIC_OBJS)
	rm -f $(STATIC_LIB)
	rm -f $(DYNAMIC_LIB)

