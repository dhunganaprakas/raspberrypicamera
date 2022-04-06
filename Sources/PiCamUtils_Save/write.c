/**
 * @file write.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation for writing image files </b>
 * @version 
 * @date 2022-03-06	Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2022-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-03-24 Remove unused variable
 * @date 2022-04-05 Add saving images for JPEG RGB
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <jpeglib.h>
#include "write.h"

/*===========================[  Function definitions  ]===================================*/

/**	Print error message and terminate program with EXIT_FAILURE return code.
*/
void errno_exit(const char* s)
{
	fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
	exit(EXIT_FAILURE);
}

/** This function writes captured buffer as a bitmap format. 
 */ 
void writebitmapimage(int width, int height, unsigned char* src, char* filename)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	/* Bitmap standard formatting rules. It does not fit in the header structure due 
	to alignment requirements, so put it outside */
	unsigned short bfType=0x4d42;     

	/* File header informations */      
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize = 2+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ height*width*3;
	bfh.bfOffBits = 0x36;

	/* BMP Image header informations */
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

	/*Write headers and pixel values */
	fwrite(&bfType,1,sizeof(bfType),file);
	fwrite(&bfh, 1, sizeof(bfh), file);
	fwrite(&bih, 1, sizeof(bih), file);
	fwrite(src, sizeof(unsigned char), width * height * 3, file);

	fclose(file);
}

/** This function writes captured image buffer as JPEG format. 
 */ 
void writejpegimageYUV(int width, int height, unsigned char* img, char* filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];
	FILE *outfile = fopen( filename, "wb" );
	if (!outfile) {
		errno_exit("jpeg");
	}

	/* Create JPEG data */
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	/* Set image parameters */
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_YCbCr;

	/* Set JPEG compression parameters to default, adjust quality setting and start conpression */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, jpegQuality, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	/* Feed pixel data */
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		row_pointer[0] = &img[cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	/* Finish compression */
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	/* Close output image file */
	fclose(outfile);
}


/** This function writes captured image buffer as JPEG format. 
 */ 
void writejpegimageRGB(int width, int height, unsigned char* img, char* filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];
	FILE *outfile = fopen( filename, "wb" );
	if (!outfile) {
		errno_exit("jpeg");
	}

	/* Create JPEG data */
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	/* Set image parameters */
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	/* Set JPEG compression parameters to default, adjust quality setting and start conpression */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, jpegQuality, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	/* Feed pixel data */
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		row_pointer[0] = &img[cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	/* Finish compression */
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	/* Close output image file */
	fclose(outfile);
}

/** This function writes captured image buffer as JPEG format. 
 */ 
void writejpeggrayscale(int width, int height, unsigned char* img, char* filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];
	FILE *outfile = fopen( filename, "wb" );
	if (!outfile) {
		errno_exit("jpeg");
	}

	/* Create JPEG data */
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	/* Set image parameters */
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 1;
	cinfo.in_color_space = JCS_GRAYSCALE;

	/* Set JPEG compression parameters to default, adjust quality setting and start conpression */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 100, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	/* Feed pixel data */
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		row_pointer[0] = &img[cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	/* Finish compression */
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	/* Close output image file */
	fclose(outfile);
}

/*==============================[  End of File  ]======================================*/
