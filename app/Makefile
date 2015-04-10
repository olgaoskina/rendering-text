NAME-STATIC=render_text-static-DONE
NAME-DYNAMIC=render_text-dynamic-DONE

LDFLAGS_A=-L$(ZLIB_PATH) -L $(PNGLIB_PATH) -L$(FREETYPELIB_PATH) -lpng -lfreetype -lm -lz 

CC=gcc
CFLAGS= -W -Wall -O3 -funroll-loops -g -DPNG_DEBUG=5

ZLIB_STATIC_LIB=libz.a
ZLIB_PATH=../zlib12

PNGLIB_STATIC_LIB=libpng.a
PNGLIB_PATH=../libpng

FREETYPELIB_STATIC_LIB=libfreetype.a
FREETYPELIB_PATH=../freetype

INCS=-I $(ZLIB_PATH) -I $(PNGLIB_PATH) -I $(FREETYPELIB_PATH)

all: clean static dynamic

static: zlib-static pnglib-static freetype-static  $(NAME-STATIC)

freetype-static: 
	make -C $(FREETYPELIB_PATH) $(FREETYPELIB_STATIC_LIB)

pnglib-static: 
	make -C $(PNGLIB_PATH) $(PNGLIB_STATIC_LIB)

zlib-static: 
	make -C $(ZLIB_PATH) $(ZLIB_STATIC_LIB)

$(NAME-STATIC): $(NAME-STATIC).o
	$(CC) -o $@ $(CFLAGS) $<  $(LDFLAGS_A)

$(NAME-STATIC).o: $(NAME-STATIC).c
	$(CC) $(INCS) -c -o $@ $<

dynamic: zlib-dynamic pnglib-dynamic freetype-dynamic  $(NAME-DYNAMIC)

freetype-dynamic: 
	make -C $(FREETYPELIB_PATH) $(FREETYPELIB_DYNAMIC_LIB)

pnglib-dynamic: 
	make -C $(PNGLIB_PATH) $(PNGLIB_DYNAMIC_LIB)

zlib-dynamic: 
	make -C $(ZLIB_PATH) $(ZLIB_DYNAMIC_LIB)

$(NAME-DYNAMIC): $(NAME-DYNAMIC).o
	$(CC) $< -o $@ $(LDFLAGS_A)

$(NAME-DYNAMIC).o: $(NAME-DYNAMIC).c
	$(CC) $(INCS) -c -o $@ $<

clean:
	make -C $(ZLIB_PATH) clean
	make -C $(PNGLIB_PATH) clean
	make -C $(FREETYPELIB_PATH) clean
	rm -f $(NAME-STATIC).o $(NAME-STATIC)