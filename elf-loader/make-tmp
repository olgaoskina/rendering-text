CC=gcc
OBJS=elf-module.o elf-module-i386.o reld.o
CFLAGS+=-Wall -Werror -Iinclude
CFLAGS_MODULE=-fno-common -fno-builtin
TARGET=reld
MODULES=mod1.mod mod2.mod

all: $(TARGET) $(MODULES)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) $(MODULES)

%.mod: %.c
	gcc-elf $(CFLAGS_MODULE) -c -o $@ $<

.PHONY: clean
