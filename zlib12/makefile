OBJS= \
    adler32.o \
    compress.o \
    crc32.o \
    deflate.o \
    gzclose.o \
    gzlib.o \
    gzread.o \
    gzwrite.o \
    infback.o \
    inffast.o \
    inflate.o \
    inftrees.o \
    trees.o \
    uncompr.o \
    zutil.o \

STATIC_OBJS=$(OBJS:%.o=%.static.o)
DYNAIC_OBJS=$(OBJS:%.o=%.dynamic.o)

INCS= -I. $(INC)

CC=gcc
C_FLAGS=

AR=ar
AR_FLAGS=rc
RANLIB=ranlib

NAME_LIB=libz
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