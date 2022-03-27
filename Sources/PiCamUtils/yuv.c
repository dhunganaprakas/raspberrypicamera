/**
 * @file yuv.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation for YUV conversion functions </b>
 * @version 
 * @date 2022-03-03 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/

#include <stdio.h>
#include <unistd.h>
#include "write.h"
#include "yuv.h"

/*===========================[  Function definitions  ]===================================*/
/**
 * In this format each four bytes is two pixels in YUV colorspace. Each four bytes has 
 * two Luminance(Y), and single Chrominances namely Chroma Blue(Cb) and Chroma Red(Cr).
 * Each Y goes to one of the pixels, and the Cb and Cr belong to both pixels. 
 * 
 */
void Convert_YUV420toYUV444(int width, int height, unsigned char* src, unsigned char* dst) 
{
    /** Sanity check for input parameters */
    if ( (NULL != src) && (NULL != dst) && (0 == width%2)&& (0 == height%2))
    {
        int row, column;
        int frame = width * height;
        int chroma_length = frame / 4;
        
		for (row = 0; row < height ; row++ ) {
			for (column = 0; column < width ; column++ ) {
				int pos = row * width + column;
                int chroma_pos = ((int)(row/2) * (int)(width/2)) + (column/2);

                /** Luminance value update */
                *(dst++) = *(src + pos);
                /** Chrominance values update */
                *(dst++) = *(src + frame + chroma_pos);
                *(dst++) = *(src + frame + chroma_length + chroma_pos);
			}
		}
    }
    else
    {
        errno_exit("YUV420 to YUV444 Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_YUV420toYUV444 */


void Convert_YUV420toBMPRGB(int width, int height, unsigned char* src, unsigned char* dst) 
{
    /** Sanity check for input parameters */
    if ( (NULL != src) && (NULL != dst) && (0 == width%2)&& (0 == height%2))
    {
        int row, column;
        int frame = width * height;
        int chroma_length = frame / 4;
        int pixel_Y, pixel_U, pixel_V;
        int dst_position;
        
		for (row = height -1; row >= 0 ; row-- ) {
			for (column = width -1; column >= 0 ; column-- ) {
				int pos = row * width + column;
                int chroma_pos = ((int)(row/2) * (int)(width/2)) + (column/2);

                /** Luminance value update */
                pixel_Y = *(src + pos);
                /** Chrominance values update */
                pixel_V = *(src + frame + chroma_pos);
                pixel_U = *(src + frame + chroma_length + chroma_pos);

                /** Luminance value update */
                *(dst++) = GETREDPIXEL_FROM_YUV(pixel_Y, pixel_V);  
                *(dst++) = GETGREENPIXEL_FROM_YUV(pixel_Y, pixel_U, pixel_V);
                *(dst++) = GETBLUEPIXEL_FROM_YUV(pixel_Y, pixel_U);            
                
			}
		}
    }
    else
    {
        errno_exit("YUV420 to RGB Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_YUV420toBMPRGB */


/*==============================[  End of File  ]======================================*/
