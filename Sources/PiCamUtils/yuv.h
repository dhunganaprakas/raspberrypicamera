/**
 * @file yuv.h
 * @author Prakash Dhungana (dhunganaprakas)
 * @brief 
 * @version 0.0.1
 * @date 2022-03-03 Initial template
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/*===========================[  Compile Flags  ]==========================================*/

#ifndef YUV_H
#define  YUV_H

/*============================[  Defines  ]=============================================*/

/**
r = y0 + ((357 * cr) >> 8) - 179;
g = y0 - (( 87 * cb) >> 8) +  44 - ((181 * cr) >> 8) + 91;
b = y0 + ((450 * cb) >> 8) - 226;
*/

/** Prevent overflow of pixel value */
#define LIMITPIXEL(x) ((x>255)?255:((x<0)?0:x))

/** Return red pixel value from YUV */
#define GETREDPIXEL_FROM_YUV(y,v)       (LIMITPIXEL( (int)(y + ((337*v) >> 8) - 179)))

/** Return red pixel value from YUV */
#define GETGREENPIXEL_FROM_YUV(y,u,v)   (LIMITPIXEL( (int)(y - (( 87*u) >> 8) - ((181*v) >> 8) + 135)))

/** Return red pixel value from YUV */
#define GETBLUEPIXEL_FROM_YUV(y, u)     (LIMITPIXEL( (int)(y + ((450*u) >> 8) - 226)))

/*===========================[  Function declarations  ]===================================*/

/**
 * @brief Convert image colorspace format from YUV420 to YUV444.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 * 
 */
void Convert_YUV420toYUV444(int width, int height, const unsigned char* src, unsigned char* dst);

/**
 * @brief Convert image colorspace format from YUV420 to YUV444.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 * 
 */
void Convert_YUV420toRGB(int width, int height, const unsigned char* src, unsigned char* dst);

#endif /** YUV_H **/

/*==============================[  End of File  ]======================================*/
