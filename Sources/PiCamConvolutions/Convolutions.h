/**
 * @file Convolutions.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for convolution methods </b>
 * @version
 * @date 2022-03-06 Initial template
 * @date 2022-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-03-24 Updates for convolution methods
 * @date 2022-03-27 Updates for mean and median filtering
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef CONVOLUTIONS_H
#define  CONVOLUTIONS_H

/*===========================[  Inclusions  ]=============================================*/

#include "Common_PiCam.h"

/*============================[  Defines  ]===============================================*/

/** Prevent overflow of pixel value */
#define LIMITCHAR(x) ((x>255)?255:((x<0)?0:x))

/** Enumeration to indicate which method to use for edge detection */
typedef enum 
{
    /** Edge detection is performed using Canny edge detection method*/
    METHOD_CANNY = 1,
    /** Edge detection is performed using Sobel edge detection method*/
    METHOD_SOBEL = 2
}EdgeDetector;

/** 3X3 Matrix to store kernel matrices */
typedef double Double_Mat3[3][3];

/** 5X5 Matrix to store kernel matrices */
typedef double Double_Mat5[5][5];

/** 3X3 Matrix to store pixel data and kernel matrices */
typedef int Mat3[3][3];

/** 5X5 Matrix to store pixel data and kernel matrices */
typedef int Mat5[5][5];

/**Structure to store return values in 2-D convolution methods */
typedef struct{
    /** Field to store return data for value obtained by applying horizontal kernal 
     * matrix in the provided pixel matrix data
    */
    int sum_x;
    /** Field to store return data for value obtained by applying vertical kernal 
     * matrix in the provided pixel matrix data
    */
    int sum_y;
}Conv2D_Return;

/*===========================[  Global Variables  ]=======================================*/

/** Variable to store lower limit for Canny edge detection. Default is set to 75 */
static int LOWER_LIMIT_CANNY = 75;

/** Variable to store upper limit for Canny edge detection. Default is set to 150 */
static int UPPER_LIMIT_CANNY = 125;

/** Variable to store limit for Sobel edge detection. Default is set to 100 */
static int LIMIT_SOBEL = 50;

/*============================[  Global Constants  ]=======================================*/

/** Kernel matrix of 3X3 size for Gaussian filtering */
static Double_Mat3 Kernel_Gaussian = {{0.0625,0.125,0.0625},{0.125,0.25,0.125},{0.0625,0.125,0.0625}};

/** Kernel matrix of 3X3 size for Sobel and Canny edge detection in horizontal direction */
static Mat3 Kernel_H_Edge = {{-1,0,1},{-2,0,2},{-1,0,1}};

/** Kernel matrix of 3X3 size for Sobel and Canny edge detection in vertical direction */
static Mat3 Kernel_V_Edge = {{-1,-2,-1},{0,0,0},{1,2,1}};

/*===========================[  Function declarations  ]==================================*/

/**
 * @brief   Function to fill the required 3X3 pixels form source image buffer to the input matrix lReturn. 
 * 
 * @param[in] row       Row Index to copy pixel values 
 * @param[in] column    Column Index to copy pixel values 
 * @param[in] width     Width of the source image
 * @param[in] src       Pointer to source image pixel data buffer
 * @param[inout] lReturn    Matrix to populate with the pixel values 
 * 
 */
static inline void Populate_PixelMat3(int row, int column, int width, unsigned char* src, Mat3 lReturn);

/**
 * @brief   Function to fill the required 5X5 pixels form source image buffer to the input matrix lReturn. 
 * 
 * @param[in] row       Row Index to copy pixel values 
 * @param[in] column    Column Index to copy pixel values 
 * @param[in] width     Width of the source image
 * @param[in] src       Pointer to source image pixel data buffer
 * @param[inout] lReturn    Matrix to populate with the pixel values 
 * 
 */
static inline void Populate_PixelMat5(int row, int column, int width, unsigned char* src, Mat5 lReturn);

/**
 * @brief   Function to perform one directional convolution's matrix multiplication from input pixel and 
 *          kernel matrix input and returns the sum on elements of the resulting matrix. The input size 
 *          of the input matrices is 3X3. 
 * 
 * @param[in] pixel     Matrix with the pixel values 
 * @param[in] kernel    3X3 Kernel Matrix to operate on image
 * @return double 
 * 
 */
static inline double Perform_Mat3Conv_1D(Mat3 pixel, Double_Mat3 kernel);

/**
 * @brief   Function to perform one directional convolution's matrix multiplication from input pixel and 
 *          kernel matrix input and returns the sum on elements of the resulting matrix. The input size 
 *          of the input matrices is 5X5. 
 * 
 * @param[in] pixel     Matrix with the pixel values 
 * @param[in] kernel    5X5 Kernel Matrix to operate on image
 * @return double 
 * 
 */
static inline double Perform_Mat5Conv_1D(Mat5 pixel, Double_Mat5 kernel);

/**
 * @brief   Function to perform two directional convolution's matrix multiplication from input pixel and 
 *          two of the kernel matrix (one for horizontal and second for vertical direction) input and returns
 *          the sum on elements of the resulting matrix. The input size of the input matrices is 3X3. 
 * 
 * @param[in] pixel     Matrix with the pixel values           
 * @param[in] kernel_H  3X3 Kernel Matrix to operate on image in horizontal direction
 * @param[in] kernel_V  3X3 Kernel Matrix to operate on image in vertical direction
 * 
 * @return Conv2D_Return    Sum of elements of matrix after convolution
 * @retval  Conv2D_Return.sum_x   Return value for input matrix pixel and kernel for horizontal
 *                                direction kernel_H
 * @retval  Conv2D_Return.sum_y   Return value for input matrix pixel and kernel for vertical 
 *                                direction kernel_V
 * 
 */
static inline Conv2D_Return Perform_Mat3Conv_2D(Mat3 pixel, Mat3 kernel_H, Mat3 kernel_V);

/**
 * @brief Function to populate detected edges.  
 * 
 * @param[in] Grad      Gradient values  
 * @param[in] method    Edge detection method
 * @param[in] width     Width of the image
 * @param[inout] dst    Pointer to destination image 
 */
static inline void Populate_Edges(Conv2D_Return Grad, EdgeDetector method, int width, int h, int v, unsigned char* dst);

/**
 * @brief Function to operate convolution for mean filtering for 3x3 matrix.
 * 
 * @param[in] pixel Input matrix to get median value from 
 * @return Std_ReturnType Calculated value from convolution 
 * 
 */
static inline Std_ReturnType Get_MeanM3(Mat3 pixel);

/**
 * @brief Function to get median value of the input 3x3 matrix.
 * 
 * @param[in] pixel Input matrix to get median value from 
 * @return Std_ReturnType Median value of input 3x3 matrix
 * 
 */
static inline Std_ReturnType Get_MedianM3(Mat3 pixel);

/**
 * @brief Function to get median value of the input 5x5 matrix.
 * 
 * @param[in] pixel Input matrix to get median value from 
 * @return Std_ReturnType Median value of input 5x5 matrix
 * 
 */
static inline Std_ReturnType Get_MedianM5(Mat5 pixel);

/**
 * @brief   Function to perform Gaussian filtering.  
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image
 * @param[in]  size     Matrix size to operate on for filtering
 * 
 */
void GaussianFilter(int width, int height, unsigned char* src, unsigned char* dst, int size);

/**
 * @brief   Function to perform Mean filtering.  
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image
 * @param[in]  size     Matrix size to operate on for filtering
 * 
 */
void MeanFilter(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief   Function to perform Median filtering.  
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to apply Gaussian filter 
 * @param[inout] dst    Pointer of destination image to save Gaussian image
 * @param[in]  size     Matrix size to operate on for filtering
 * 
 */
void MedianFilter(int width, int height, unsigned char* src, unsigned char* dst, int size);

/**
 * @brief   Function to perform Edge detection. 
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @param[in] src       Pointer of source image to detect Canny Edge 
 * @param[inout] dst    Pointer of destination image to save Canny Edge
 * @param[in] method    Method based on which edge detection is performed 
 * 
 */
void Edge_Detector(int width, int height, unsigned char* src, unsigned char* dst, EdgeDetector method);

#endif /** CONVOLUTIONS_H **/

/*==============================[  End of File  ]========================================*/
