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
FT_Error (*FT_Init_FreeType1)( FT_Library  * );
char* (*fun)(void);

int main(int argc, char **argv) {
		FT_Library     library;

	void* handle = dlopen("../freetype/libfreetype.so",RTLD_LAZY);
//	FT_Init_FreeType1 = dlsym(handle,"FT_Init_FreeType");
	fun = dlsym(handle,"from_freetype");
	printf("%s\n", dlerror());
	printf("%s\n", (*fun)());
	dlclose(handle);
  return 0;
}

