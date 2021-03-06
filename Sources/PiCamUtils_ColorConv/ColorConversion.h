/**
 * @file ColorConversion.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for color-space conversion functions </b>
 * @version
 * @date 2022-03-03 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2022-03-28 Rename and move to appropriate folder
 * @date 2022-04-03 Update color conversion functions for HSV
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */


/*===========================[  Compile Flags  ]==========================================*/

#ifndef YUV_H
#define  YUV_H

/*===========================[  Inclusions  ]===========================================*/

#include "Common_PiCam.h"

/*============================[  Defines  ]=============================================*/

/** \addtogroup function_macros	  
 *  @{
 */

/** Conversion from YUV color space to RGB \n
 *   r = y0 + ((357 * cr) >> 8) - 179;  \n
 *   g = y0 - (( 87 * cb) >> 8) +  44 - ((181 * cr) >> 8) + 91; \n
 *   b = y0 + ((450 * cb) >> 8) - 226;  \n
*/

/** Return red pixel value from YUV */
#define GETREDPIXEL_FROM_YUV(y,v)       (LIMITPIXEL( (int)(1.164*(y-16) + 1.596*(v-128))))

/** Return red pixel value from YUV */
#define GETGREENPIXEL_FROM_YUV(y,u,v)   (LIMITPIXEL( (int)(1.164*(y-16) - 0.392*(u-128) -0.813*(v-128))))

/** Return red pixel value from YUV */
#define GETBLUEPIXEL_FROM_YUV(y, u)     (LIMITPIXEL( (int)(1.164*(y-16) + 2.017*(u-128))))

/** @} */

/*===========================[  Function declarations  ]===================================*/

/** \addtogroup interface_functions Interface Functions	  
 *  @{
 */

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
 * 
 */
void Convert_YUV420toRGB444(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief Convert image colorspace format from YUV420 to RGB444.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 * 
 */
void Convert_YUV444toRGB444(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief Convert image colorspace format from YUV420 to RGB444.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 * 
 */
void Convert_RGB444toHSV444(int width, int height, unsigned char* src, u_int16_t* dst);

/**
 * @brief Convert image colorspace format from YUV420 to RGB444.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to change format 
 * @param[inout] dst    Pointer of destination image to save the changed format
 * 
 */
void Convert_HSV444toRGB444(int width, int height, u_int16_t* src, unsigned char* dst);

/** @} */

#endif /** YUV_H **/

/*==============================[  End of File  ]======================================*/
