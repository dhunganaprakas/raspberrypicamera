/**
 * @file write.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <jpeglib.h>
#include "write.h"

/**
	Print error message and terminate program with EXIT_FAILURE return code.

	\param s error message to print
*/
void errno_exit(const char* s)
{
	fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
	exit(EXIT_FAILURE);
}

void writebitmapimage(int width, int height, unsigned char* src, char* filename)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	/* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
	unsigned short bfType=0x4d42;           
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize = 2+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ height*width*3;
	bfh.bfOffBits = 0x36;

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 5000;
	bih.biYPelsPerMeter = 5000;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	FILE *file = fopen(filename, "wb");
	if (!file)
    {
        printf("Could not write file\n");
        return;
    }

	/*Write headers*/
	fwrite(&bfType,1,sizeof(bfType),file);
	fwrite(&bfh, 1, sizeof(bfh), file);
	fwrite(&bih, 1, sizeof(bih), file);

	unsigned char *pixel = src + 3*height*width;

	/*Write bitmap*/
	for (int x = bih.biHeight-1; x >=0; x--) /*Scanline loop backwards*/
    {
        for (int y = bih.biWidth -1; y >= 0; y--) /*Column loop forwards*/
        {
            /*compute some pixel values*/
            unsigned char r = *(pixel--);
            unsigned char g = *(pixel--);
            unsigned char b = *(pixel--);
            fwrite(&b, 1, 1, file);
            fwrite(&g, 1, 1, file);
            fwrite(&r, 1, 1, file);
        }
    }
	fclose(file);
}

void writejpegimage(int width, int height, unsigned char* img, char* filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];
	FILE *outfile = fopen( filename, "wb" );

	// try to open file for saving
	if (!outfile) {
		errno_exit("jpeg");
	}

	// create jpeg data
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	// set image parameters
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_YCbCr;

	// set jpeg compression parameters to default
	jpeg_set_defaults(&cinfo);
	// and then adjust quality setting
	jpeg_set_quality(&cinfo, jpegQuality, TRUE);

	// start compress
	jpeg_start_compress(&cinfo, TRUE);

	// feed data
	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer[0] = &img[cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	// finish compression
	jpeg_finish_compress(&cinfo);

	// destroy jpeg data
	jpeg_destroy_compress(&cinfo);

	// close output file
	fclose(outfile);
}
