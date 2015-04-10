#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define MAX_LEN 100   // Max len of text
#define WIDTH   1000  // Width of png-image
#define HEIGHT  200   // Height of png-image

unsigned char image[HEIGHT][WIDTH];	// Bitmap of png-image

typedef struct {
	char *font_file;
	char *text;
	int size;
	int *out_file;
} config_t;

char *parse_args(int argc, char **argv, config_t *conf) {
	memset(conf, 0, sizeof(config_t));
	conf->size = 72;

	if (argc < 2) {
		return "missing font file argument";
	} else if (argc < 3) {
		return "missing text argument";
	}

	conf->font_file = argv[1];
	conf->text = argv[2];
	conf->out_file = argv[3]; 

	if (argc > 4) {
		conf->size = atoi(argv[4]);
	}

	return NULL;
}

char *render_png(char *output_png) {
// Open file to write
  FILE *f = fopen(output_png, "wb");
  if (!f) return "failed to open output file";

// Allocate and initialize a png_struct structure for writing PNG file
  png_structp png_out = png_create_write_struct(
                            PNG_LIBPNG_VER_STRING, 	// version string of the library.
                            NULL, 									// user defined struct for error functions
                            NULL, 									// user defined function for printing errors and aborting
                            NULL); 									//user defined function for warnings
  if (!png_out) return "failed to create png write struct";

// allocate and initialize a png_info structure
  png_infop png_info = png_create_info_struct(png_out);
  if (!png_info) return "failed to create png info struct";

// Set error handling. The png_jmpbuf() macro, used in error handling
  if (setjmp(png_jmpbuf(png_out))) return "png init io error";
  
// The png_init_io() function takes our file stream pointer (infile) and stores it in the png_ptr struct for later use
  png_init_io(png_out, f);

  if (setjmp(png_jmpbuf(png_out)))
		return "IHDR write error";

// set the PNG_IHDR chunk information. IHDR - file header provides basic information about the image. It must have been the first Chunk
  png_set_IHDR(png_out,
               png_info,
				       WIDTH, 												// width of the image in pixels
               HEIGHT, 												// height of the image in pixels
               8,															// depth of one of the image channels
               PNG_COLOR_TYPE_GRAY,						// describes which color/alpha channels are present
               PNG_INTERLACE_NONE, 						// interlace_type
               PNG_COMPRESSION_TYPE_DEFAULT, 	// compression_type
               PNG_FILTER_TYPE_DEFAULT); 			// filter_method

  png_write_info(png_out, png_info);

  if (setjmp(png_jmpbuf(png_out)))
		return "png write error";

// Write bitmap to png in rows
  int i, j;
  for (i = 0; i < HEIGHT; ++i) {
  	unsigned char *rowptr = (unsigned char *)image + (WIDTH * i);
  	png_write_row(png_out, rowptr);
  }

  if (setjmp(png_jmpbuf(png_out)))
		return "png end error";
  png_write_end(png_out, NULL);

  fclose(f);
  return NULL;
}

void my_draw_bitmap( FT_Bitmap* bitmap, FT_Int x, FT_Int y) {
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;

  for ( i = x, p = 0; i < x_max; i++, p++ ) {
    for ( j = y, q = 0; j < y_max; j++, q++ ) {
      if ( i < 0 || j < 0 || i >= WIDTH || j >= HEIGHT ) {
        continue;
      }
      image[j][i] |= bitmap->buffer[q * bitmap->width + p];
    }
  }
}

char *render_text(config_t conf) {
	int            pen_x;
	int            pen_y;
	int            n;

	FT_Library     library;
	FT_Face        face; 
	FT_GlyphSlot   slot;
	FT_Error       error;

// Initialize a new FreeType library object
	error = FT_Init_FreeType( &library );
	if ( error ) return "Can't initialize FreeType library";

// Open a font by its pathname.
	error = FT_New_Face( 	library, 				// A handle to the library resource.
		                 		conf.font_file, // A path to the font file.
		                 		0, 							// The index of the face within the font.
		                 		&face ); 

	if ( error == FT_Err_Unknown_File_Format ) return "Unknown file format for font";
	else if ( error ) return "Can't create a face";

// Request the nominal size
	error = FT_Set_Pixel_Sizes(	face,   		// handle to face object 
															0,      		// pixel_width           
															conf.size );
	slot = face->glyph;
	pen_x = 100;
	pen_y = 100;

	for ( n = 0; n < strlen(conf.text); n++ ) {
		FT_UInt  glyph_index;

// Return the glyph index of a given character code
		glyph_index = FT_Get_Char_Index(face, conf.text[n]);

// Load a single glyph into the glyph slot of a face object
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		if ( error ) continue;  // ignore errors 

// Convert a given glyph image to a bitmap
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if ( error )
		  continue;

// Draw bitmap 
			my_draw_bitmap(&slot->bitmap,
			        pen_x + slot->bitmap_left,
			        pen_y - slot->bitmap_top);

// Increment pen position 
		pen_x += slot->advance.x >> 6;
		pen_y += slot->advance.y >> 6; /* not useful for now */
	}
	return NULL;
}

int main(int argc, char **argv) {
  config_t conf;
  char *conf_err = parse_args(argc, argv, &conf);
  
  if (conf_err != NULL) {
    printf("Error: %s\n", conf_err);
    puts("Usage: render-text <font> <text> <output file> [<size>]");
    return 1;
  }

  printf("font: %s, text: %s, output: %s, size: %d\n",
         conf.font_file,
         conf.text,
         conf.out_file,
         conf.size);

	conf_err = render_text(conf);
  if (conf_err != NULL) {
    printf("Error: %s\n", conf_err);
    return 1;
  }
	
  conf_err = render_png(conf.out_file);
  if (conf_err != NULL) {
    printf("Error: %s\n", conf_err);
    return 1;
  }
  return 0;
}

