
OBJS= \
	elf-module.o \
	elf-module-i386.o \
	
STATIC_OBJS=$(OBJS:%.o=%.static.o)
DYNAMIC_OBJS=$(OBJS:%.o=%.dynamic.o)

INCS= -I. -Iinclude

CC=gcc
C_FLAGS=

AR=ar
AR_FLAGS=rc
RANLIB=ranlib

NAME_LIB=libelf
STATIC_LIB=$(NAME_LIB).a
DYNAMIC_LIB=$(NAME_LIB).so


all: $(STATIC_LIB)

$(STATIC_LIB):$(STATIC_OBJS)
	$(AR) $(AR_FLAGS) $@ $(STATIC_OBJS)
	$(RANLIB) $@

%.static.o : %.c
	$(CC) $(INCS) $(CFLAGS) -c $< -o $@

$(DYNAMIC_LIB):$(DYNAMIC_OBJS)
	$(CC) -shared -o $@ $<

%.dynamic.o : %.c
	$(CC) $(INCS) -fpic $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(STATIC_OBJS)
	rm -f $(DYNAMIC_OBJS)
	rm -f $(STATIC_LIB)
	rm -f $(DYNAMIC_LIB)
