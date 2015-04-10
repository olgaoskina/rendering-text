
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
DYNAIC_OBJS=$(OBJS:%.o=%.dynamic.o)

INCS= -I. $(INC)

CC=gcc
C_FLAGS=

AR=ar
AR_FLAGS=rc
RANLIB=ranlib

NAME_LIB=libfreetype
STATIC_LIB=$(NAME_LIB).a
DYNAMIC_LIB=$(NAME_LIB).so

all: clean $(STATIC_LIB) $(DYNAMIC_LIB)

$(STATIC_LIB):$(STATIC_OBJS)
	$(AR) $(AR_FLAGS) $@ $(STATIC_OBJS)
	$(RANLIB) $@

%.static.o : %.c
	$(CC) $(CFLAGS) -c $<

$(DYNAMIC_LIB):$(DYNAIC_OBJS)
	$(CC) -shared -o $@ $<

%.static.o : %.c
	$(CC) -fpic $(CFLAGS) -c $<

clean: 
	rm -f $(STATIC_OBJS)
	rm -f $(DYNAIC_OBJS)
	rm -f $(STATIC_LIB)