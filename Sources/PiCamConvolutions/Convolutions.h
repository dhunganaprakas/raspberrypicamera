/**
 * @file Convolutions.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for convolution methods </b>
 * @version
 * @date 2022-03-06 Initial template
 * @date 2033-03-23 Updates for Gaussian filter and Edge detection
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef CONVOLUTIONS_H
#define  CONVOLUTIONS_H

/*===========================[  Inclusions  ]=============================================*/


/*============================[  Defines  ]===============================================*/

/** Prevent overflow of pixel value */
#define LIMITCHAR(x) ((x>255)?255:((x<0)?0:x))

typedef enum 
{
    METHOD_CANNY = 1,
    METHOD_SOBEL = 2,
    METHOD_INVALID = 3
}EdgeDetector;

/*===========================[  Global Variables  ]=======================================*/

/** Variable to store lower limit for Canny edge detection. Default is set to 75 */
static int LOWER_LIMIT_CANNY = 50;

/** Variable to store upper limit for Canny edge detection. Default is set to 150 */
static int UPPER_LIMIT_CANNY = 175;

/** Variable to store limit for Sobel edge detection. Default is set to 100 */
static int LIMIT_SOBEL = 50;

/*============================[  Global Constants  ]=======================================*/

/** Kernel matrix of 3X3 size for Gaussian filtering */
static double Kernel_Gaussian[3][3] = {{0.0625,0.125,0.0625},{0.125,0.25,0.125},{0.0625,0.125,0.0625}};

/** Kernel matrix of 3X3 size for Sobel and Canny edge detection in horizontal direction */
static const int Kernel_H_Edge[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};

/** Kernel matrix of 3X3 size for Sobel and Canny edge detection in vertical direction */
static const int Kernel_V_Edge[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

/*===========================[  Function declarations  ]==================================*/

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image 
 * 
 */
void GaussianFilter(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image 
 * 
 */
void MeanFilter(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image 
 * 
 */
void MedianFilter(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to detect Canny Edge 
 * @param[inout] dst    Pointer of destination image to save Canny Edge
 * 
 */
void Edge_Detector(int width, int height, unsigned char* src, unsigned char* dst, EdgeDetector method);

#endif /** CONVOLUTIONS_H **/

/*==============================[  End of File  ]========================================*/
