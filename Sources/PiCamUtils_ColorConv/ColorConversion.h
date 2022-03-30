/**
 * @file ColorConversion.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for YUV conversion functions </b>
 * @version
 * @date 2022-03-03 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2022-03-28 Rename and move to appropriate folder
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */


/*===========================[  Compile Flags  ]==========================================*/

#ifndef YUV_H
#define  YUV_H

/*============================[  Defines  ]=============================================*/

/** Conversion from YUV color space to RGB 
 *   r = y0 + ((357 * cr) >> 8) - 179;
 *   g = y0 - (( 87 * cb) >> 8) +  44 - ((181 * cr) >> 8) + 91;
 *   b = y0 + ((450 * cb) >> 8) - 226;
*/

/** Prevent overflow of pixel value */
#define LIMITPIXEL(x) ((x>255)?255:((x<0)?0:x))

/** Return red pixel value from YUV */
#define GETREDPIXEL_FROM_YUV(y,v)       (LIMITPIXEL( (int)(1.164*(y-16) + 1.596*(v-128))))

/** Return red pixel value from YUV */
#define GETGREENPIXEL_FROM_YUV(y,u,v)   (LIMITPIXEL( (int)(1.164*(y-16) - 0.392*(u-128) -0.813*(v-128))))

/** Return red pixel value from YUV */
#define GETBLUEPIXEL_FROM_YUV(y, u)     (LIMITPIXEL( (int)(1.164*(y-16) + 2.017*(u-128))))

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
void Convert_YUV420toYUV444(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief Converts YUV420 pixels to bitmap formatting for RGB colorspace.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 * 
 */
void Convert_YUV420toBMPRGB(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief Convert image colorspace format from YUV420 to RGB444.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 */
void Convert_YUV420toRGB444(int width, int height, unsigned char* src, unsigned char* dst);

#endif /** YUV_H **/

/*==============================[  End of File  ]======================================*/
