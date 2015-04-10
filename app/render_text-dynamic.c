#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>
#include <zlib.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <reld.c>



#define MAX_LEN 100   // Max len of text
#define WIDTH   1000  // Width of png-image
#define HEIGHT  200   // Height of png-image

int main(int argc, char **argv) {
	verbose = 1;
	load_module("../zlib12/libz.so");
	char* (*fun)(void) = resolve_symbol(NULL, "fromZLib");
	printf("%s\n", (*fun)());
  return 0;
}

