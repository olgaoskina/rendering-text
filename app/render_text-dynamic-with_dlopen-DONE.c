#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>
#include <zlib.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <dlfcn.h>



#define MAX_LEN 100   // Max len of text
#define WIDTH   1000  // Width of png-image
#define HEIGHT  200   // Height of png-image

//char* fromZLib();	

int main(int argc, char **argv) {
	void* handle = dlopen("../zlib12/libz.so",RTLD_LAZY);
	char*(*fun)(void) = dlsym(handle,"fromZLib");
	printf("%s\n", (*fun)());
	dlclose(handle);
  return 0;
}

