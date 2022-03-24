/**
 * @file Convolutions.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Source for implementation of convolution methods </b>
 * @version 
 * @date 2022-03-06 Initial template
 * @date 2033-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-03-24 Updates for convolution methods
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/


/*===========================[  Inclusions  ]=============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Convolutions.h"

/*===========================[ Global Variables  ]========================================*/



/*===========================[  Function definitions  ]===================================*/
/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void Populate_PixelMat3(int row, int column, int width, unsigned char* src, Mat3 lReturn)
{
	int i, j, position;

	for(i = 0 ; i < 3 ; i++)
	{
		for(j = 0 ; j < 3 ; j++)
		{
			position = (row - 1 + i)*width + (column - 1 + j);
			lReturn[i][j] =  *(src + position);
		}
	}		
}/* End of function Populate_PixelMat3 */

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void Populate_PixelMat5(int row, int column, int width, unsigned char* src, Mat5 lReturn)
{
	int i, j, position;

	for(i = 0 ; i < 5 ; i++)
	{
		for(j = 0 ; j < 5 ; j++)
		{
			position = (row - 2 + i)*width + (column - 2 + j);
			lReturn[i][j] =  *(src + position);
		}
	}
}/* End of function Populate_PixelMat5 */

/**
 * 
 */ 
static inline double Perform_Mat3Conv_1D(Mat3 pixel, Double_Mat3 kernel)
{
	int i, j, temp;
	double lReturn;

	for(i = 0; i < 3; i++)
	{					
		for(j = 0; j < 3; j++)
		{
			for(temp = 0; temp < 3; temp++)
			{				
				lReturn +=  (double)kernel[i][temp] * pixel[temp][j] ;		
			}												
		}
	}

	return lReturn;
}/* End of function Perform_Mat3Conv_1D */

/**
 * 
 */ 
static inline double Perform_Mat5Conv_1D(Mat5 pixel, Double_Mat5 kernel)
{
	int i, j, temp;
	double lReturn;

	for(i = 0; i < 5; i++)
	{					
		for(j = 0; j < 5; j++)
		{
			for(temp = 0; temp < 5; temp++)
			{				
				lReturn +=  (double)kernel[i][temp] * pixel[temp][j];		
			}												
		}
	}

	return lReturn;
}/* End of function Perform_Mat5Conv_1D */ 

/**
 * 
 */ 
static inline Conv2D_Return Perform_Mat3Conv_2D(Mat3 pixel, Mat3 kernel_H, Mat3 kernel_V)
{
	int row, column, temp;
	Conv2D_Return lReturn;
	lReturn.sum_x = 0;
	lReturn.sum_y = 0;

	for(row = 0; row < 3; row++)
	{
		for(column = 0; column < 3; column++)
		{
			for(temp = 0; temp < 3; temp++)
			{			
				lReturn.sum_x += kernel_H[row][temp] * pixel[temp][column] ;
				lReturn.sum_y += kernel_V[row][temp] * pixel[temp][column] ;
			}						
		}
	}

	return lReturn;
}/* End of function Perform_Mat3Conv_2D */

/**
 * 
 */ 
void GaussianFilter(int width, int height, unsigned char* src, unsigned char* dst)
{
    int x, y;
	unsigned char pixel;
	Mat3 mat_pixel;
	
	/* TODO: Replace with function call to copy border pixels of width 1 */
	memcpy(dst, src, width*height);

    for(x = 1; x < height -1 ; x++)
    {
		for(y = 1; y < width -1 ; y++)
        {					
			Populate_PixelMat3(x, y, width, src, mat_pixel);
			double blur_pixel = Perform_Mat3Conv_1D(mat_pixel, Kernel_Gaussian);			
			pixel = LIMITCHAR((int)(blur_pixel/3));					
			*(dst+x*width + y) = pixel;
		}
	}		

}/* End of function GaussianFilter */

/**
 * 
 */ 
void Edge_Detector(int width, int height, unsigned char* src, unsigned char* dst, EdgeDetector method)
{
	int x, y;

	/* TODO: Replace with function call to copy border pixels of width 1 */
	memcpy(dst, src, width*height);

	for(x = 1; x < height - 1; x++)
	{
		for(y = 1; y < width - 1; y++)
		{
			int Gx, Gy;
			unsigned int intensity = 0;
	
			Mat3 mat_pixel;
			Populate_PixelMat3(x, y, width, src, mat_pixel);
			Conv2D_Return retval = Perform_Mat3Conv_2D(mat_pixel, Kernel_H_Edge, Kernel_V_Edge);				

			Gx = retval.sum_x;
			Gy = retval.sum_y;
			unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
			LIMITCHAR(length);								

			switch ( method)
			{
				case METHOD_CANNY:
					if ((length > LOWER_LIMIT_CANNY) && (length < UPPER_LIMIT_CANNY))
						*(dst + x*width + y) = 255;
					else
						*(dst + x*width + y) = 0;
					break;

				case METHOD_SOBEL:
					if ( length > LIMIT_SOBEL)
						*(dst + x*width + y) = 255;
					else
						*(dst + x*width + y) = 0;
					break;

				default:
					printf("Invalid method provided for edge detection.\n");
					break;
			}
		}
	}

}/* End of function Edge_Detector */


/*==============================[  End of File  ]========================================*/
