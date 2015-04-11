NAME_STATIC=render_text-static-DONE
NAME_DYNAMIC=render_text_dynamic
#NAME_DYNAMIC=render_text-dynamic-with_dlopen-DONE
#NAME_DYNAMIC=dynamic

LDFLAGS_A=-L$(ZLIB_PATH) -L $(PNGLIB_PATH) -L$(FREETYPELIB_PATH) -lfreetype -lm -lpng -lz
#LDFLAGS_D=-L$(ELF_PATH) -ldl -lelf
LDFLAGS_D=-ldl

CC=gcc
CFLAGS= -W -Wall -O3 -funroll-loops -g -DPNG_DEBUG=5

ZLIB_STATIC_LIB=libz.a
ZLIB_DYNAMIC_LIB=libz.so
ZLIB_PATH=../zlib12

PNGLIB_STATIC_LIB=libpng.a
PNGLIB_DYNAMIC_LIB=libpng.so
PNGLIB_PATH=../libpng

FREETYPELIB_STATIC_LIB=libfreetype.a
FREETYPELIB_DYNAMIC_LIB=libfreetype.so
FREETYPELIB_PATH=../freetype

ELF_PATH=../elf-loader

INCS=-I $(ZLIB_PATH) -I $(PNGLIB_PATH) -I $(FREETYPELIB_PATH) -I$(ELF_PATH) -I$(ELF_PATH)/include

all: clean static 

static: zlib-static pnglib-static freetype-static  $(NAME_STATIC)
	echo 'DONE!'

dynamic: zlib-dynamic pnglib-dynamic freetype-dynamic  $(NAME_DYNAMIC)
	echo 'DONE!'

freetype-static: 
	make -C $(FREETYPELIB_PATH) $(FREETYPELIB_STATIC_LIB)

pnglib-static: 
	make -C $(PNGLIB_PATH) $(PNGLIB_STATIC_LIB)

zlib-static: 
	make -C $(ZLIB_PATH) $(ZLIB_STATIC_LIB)

$(NAME_STATIC): $(NAME_STATIC).o
	$(CC) $<  $(LDFLAGS_A) -o $@

$(NAME_STATIC).o: $(NAME_STATIC).c
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

freetype-dynamic: 
	make -C $(FREETYPELIB_PATH) $(FREETYPELIB_DYNAMIC_LIB)

pnglib-dynamic: 
	make -C $(PNGLIB_PATH) $(PNGLIB_DYNAMIC_LIB)

zlib-dynamic: 
	make -C $(ZLIB_PATH) $(ZLIB_DYNAMIC_LIB)

$(NAME_DYNAMIC): $(NAME_DYNAMIC).o
	$(CC) $< -o $@ $(LDFLAGS_D)

$(NAME_DYNAMIC).o: $(NAME_DYNAMIC).c
	$(CC) $(INCS) -c -o $@ $<

clean:
	make -C $(ZLIB_PATH) clean
	make -C $(PNGLIB_PATH) clean
	make -C $(FREETYPELIB_PATH) clean
	rm -f $(NAME_STATIC).o $(NAME_STATIC)
	rm -f $(NAME_DYNAMIC).o $(NAME_DYNAMIC)

