/**
 * @file Convolutions.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for convolution methods </b>
 * @version
 * @date 2022-03-06 Initial template
 * @date 2022-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-03-24 Updates for convolution methods
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
 * @brief 
 * 
 * @param[in] row       Row Index to copy pixel values 
 * @param[in] column    Column Index to copy pixel values 
 * @param[in] width     Width of the source image
 * @param[in] src       Pointer to source image pixel data buffer
 * @param[inout] lReturn    Matrix to populate with the pixel values 
 */
static inline void Populate_PixelMat3(int row, int column, int width, unsigned char* src, Mat3 lReturn);

/**
 * @brief 
 * 
 * @param[in] row       Row Index to copy pixel values 
 * @param[in] column    Column Index to copy pixel values 
 * @param[in] width     Width of the source image
 * @param[in] src       Pointer to source image pixel data buffer
 * @param[inout] lReturn    Matrix to populate with the pixel values 
 */
static inline void Populate_PixelMat5(int row, int column, int width, unsigned char* src, Mat5 lReturn);

/**
 * @brief 
 * 
 * @param[in] pixel     Matrix with the pixel values 
 * @param[in] kernel    3X3 Kernel Matrix to operate on image
 * @return double 
 */
static inline double Perform_Mat3Conv_1D(Mat3 pixel, Double_Mat3 kernel);

/**
 * @brief 
 * 
 * @param[in] pixel     Matrix with the pixel values 
 * @param[in] kernel    5X5 Kernel Matrix to operate on image
 * @return double 
 */
static inline double Perform_Mat5Conv_1D(Mat5 pixel, Double_Mat5 kernel);

/**
 * @brief 
 * 
 * @param[in] pixel     Matrix with the pixel values           
 * @param[in] kernel_H  3X3 Kernel Matrix to operate on image in horizontal direction
 * @param[in] kernel_V  3X3 Kernel Matrix to operate on image in vertical direction
 * @return Conv2D_Return 
 */
static inline Conv2D_Return Perform_Mat3Conv_2D(Mat3 pixel, Mat3 kernel_H, Mat3 kernel_V);

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
