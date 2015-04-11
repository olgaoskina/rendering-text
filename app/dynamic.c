#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>
#include <zlib.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <dlfcn.h>

int main(int argc, char **argv) {
// Open shared libraries
	void* handle = dlopen("../zlib12/libz.so",RTLD_LAZY);
	void* handle_png = dlopen("../libpng/libpng.so",RTLD_LAZY);
	void* handle_fr = dlopen("../freetype/libfreetype.so",RTLD_LAZY);

// Load functions
	char*(*fun)(int) = dlsym(handle,"fromZLib");
	char*(*fun_png)(int) = dlsym(handle_png,"fromPng");
	char*(*fun_fr)(int) = dlsym(handle_fr,"fromFreetype");

// Print last error
	printf("ERROR: %s\n", dlerror());

// Call functions
	printf("%s\n", (*fun)(10));
	printf("%s\n", (*fun_png)(11));
	printf("%s\n", (*fun_fr)(12));

// Close Libraries
	dlclose(handle);
	dlclose(handle_png);
	dlclose(handle_fr);
  return 0;
}

