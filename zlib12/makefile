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
DYNAMIC_OBJS=$(OBJS:%.o=%.dynamic.o)

INCS= -I. $(INC)

CC=gcc
CFLAGS=
CFLAGS_D=-c -shared -fPIC -lc

AR=ar
AR_FLAGS=rc
RANLIB=ranlib

NAME_LIB=libz
STATIC_LIB=$(NAME_LIB).a
DYNAMIC_LIB=$(NAME_LIB).so

all: clean $(STATIC_LIB) 

$(STATIC_LIB):$(STATIC_OBJS)
	$(AR) $(AR_FLAGS) $@ $(STATIC_OBJS)
	$(RANLIB) $@

%.static.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#$(DYNAMIC_LIB):$(DYNAMIC_OBJS)
#	$(CC) -shared -o $@ $<
$(DYNAMIC_LIB):$(DYNAMIC_OBJS)
	$(LD) -shared -o $@ $(DYNAMIC_OBJS)

%.dynamic.o : %.c
	$(CC) $(CFLAGS_D) $< -o $@

clean: 
	rm -f $(STATIC_OBJS)
	rm -f $(DYNAMIC_OBJS)
	rm -f $(STATIC_LIB)
	rm -f $(DYNAMIC_LIB)

