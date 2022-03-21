/**
 * @file Convolutions.h
 * @author Prakash Dhungana (dhunganaprakas)
 * @brief Header for convolution methods 
 * @version 0.0.1
 * @date 2022-03-06 Initial template
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for documentation */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef CONVOLUTIONS_H
#define  CONVOLUTIONS_H

/*===========================[  Inclusions  ]=============================================*/


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
void GaussianFilter(int width, int height, const unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image 
 * 
 */
void MeanFilter(int width, int height, const unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image 
 * 
 */
void MedianFilter(int width, int height, const unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to detect Canny Edge 
 * @param[inout] dst    Pointer of destination image to save Canny Edge
 * 
 */
void CannyEdge_Detector(int width, int height, const unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to detect Sobel Edge 
 * @param[inout] dst    Pointer of destination image to save Sobel Edge
 *  
 */
void SobelEdge_Detector(int width, int height, const unsigned char* src, unsigned char* dst);

#endif /** CONVOLUTIONS_H **/

/*==============================[  End of File  ]========================================*/
