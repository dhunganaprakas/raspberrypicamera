/**
 * @file Convolutions.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Source for implementation of convolution methods </b>
 * @version 
 * @date 2022-03-06 Initial template
 * @date 2033-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-03-24 Updates for convolution methods
 * @date 2022-03-27 Updates for mean and median filtering
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
 * 
 */
static inline void Populate_Edges(Conv2D_Return Grad, EdgeDetector method, int width, int h, int v, unsigned char* dst)
{
	int Gx = Grad.sum_x;
	int Gy = Grad.sum_y;
	unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
	LIMITCHAR(length);								

	switch (method)
	{
		case METHOD_CANNY:
			if ((length > LOWER_LIMIT_CANNY) && (length < UPPER_LIMIT_CANNY))
				*(dst + v*width + h) = 255;
			else
				*(dst + v*width + h) = 0;
			break;

		case METHOD_SOBEL:
			if ( length > LIMIT_SOBEL)
				*(dst + v*width + h) = 255;
			else
				*(dst + v*width + h) = 0;
			break;

		default:
			printf("Invalid method provided for edge detection.\n");
			break;
	}

}/* End of function Populate_Edges */

/** 
 * 
 */
static inline Std_ReturnType Get_MeanM3(Mat3 pixel)
{
	int i, j, temp, lreturn; 
	double sum;

	for(i = 0 ; i < 3 ; i++)
	{
		for(j = 0 ; j < 3 ; j++)
		{
			for(temp = 0; temp < 3; temp++)
			{			
				sum += (double) (0.3333 * pixel[temp][j]) ;
			}
		}
	}

	lreturn = (int) sum;

	return lreturn;

}/* End of function Get_MeanM3 */

/** 
 * 
 */
static inline Std_ReturnType Get_MedianM3(Mat3 pixel)
{
	int i, j; 
	int ip_array[9];
	int temp = 0;

	for(i = 0 ; i < 3 ; i++)
	{
		for(j = 0 ; j < 3 ; j++)
		{
			ip_array[temp] = pixel[i][j];
			temp++;
		}
	}

	for (i = 0; i < 9; i ++)
	{
		for (j = 0; j <= i; j++)
		{
			if (ip_array[j] < ip_array[j+1])
			{
				temp = ip_array[j+1];
				ip_array[j+1] = ip_array[j];
				ip_array[j] = temp;
			}
		}
	}

	return ip_array[4];

}/* End of function Get_MedianM3 */

/** 
 * 
 */
static inline Std_ReturnType Get_MedianM5(Mat5 pixel)
{
	int i, j; 
	int ip_array[25];
	int temp = 0;

	for(i = 0 ; i < 5 ; i++)
	{
		for(j = 0 ; j < 5 ; j++)
		{
			ip_array[temp] = pixel[i][j];
			temp++;
		}
	}

	for (i = 0; i < 25; i ++)
	{
		for (j = 0; j <= i; j++)
		{
			if (ip_array[j] < ip_array[j+1])
			{
				temp = ip_array[j+1];
				ip_array[j+1] = ip_array[j];
				ip_array[j] = temp;
			}
		}
	}

	return ip_array[12];

}/* End of function Get_MedianM5 */

/**
 * 
 */ 
void GaussianFilter(int width, int height, unsigned char* src, unsigned char* dst, int size)
{
	Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
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
				*(dst + x*width + y) = pixel;
			}
		}
	}
	else
	{
		printf("Invalid input parameters provided.\n");
	}		

}/* End of function GaussianFilter */

/**
 * 
 */ 
void Edge_Detector(int width, int height, unsigned char* src, unsigned char* dst, EdgeDetector method)
{
	Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
	{
		int x, y;
		/* TODO: Replace with function call to copy border pixels of width 1 */
		memcpy(dst, src, width*height);

		for(x = 1; x < height - 1; x++)
		{
			for(y = 1; y < width - 1; y++)
			{
				Mat3 mat_pixel;
				Populate_PixelMat3(x, y, width, src, mat_pixel);
				Conv2D_Return retval = Perform_Mat3Conv_2D(mat_pixel, Kernel_H_Edge, Kernel_V_Edge);
				Populate_Edges(retval, method, width, y, x, dst);
			}
		}
	}
	else
	{
		printf("Invalid input parameters provided.\n");
	}

}/* End of function Edge_Detector */

/** 
 * 
 */
void MeanFilter(int width, int height, unsigned char* src, unsigned char* dst)
{
	Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
	{
		int x, y, ret_m3;
		Mat3 mat3_pixel; 				
		/* TODO: Replace with function call to copy border pixels of width 1 */
		memcpy(dst, src, width*height);
		
		for(x = 1; x < height - 1; x++)
		{
			for(y = 1; y < width - 1; y++)
			{
				Populate_PixelMat3(x, y, width, src, mat3_pixel);
				ret_m3 = Get_MeanM3(mat3_pixel);							
				*(dst + x*width + y) = LIMITCHAR(ret_m3/9);
			}
		}	
	}
	else
	{
		printf("Invalid input parameters provided.\n");
	}

}/* End of function MeanFilter */

/** 
 * 
 */
void MedianFilter(int width, int height, unsigned char* src, unsigned char* dst, int size)
{
	Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
	{
		int x, y, ret_m3, ret_m5;
		Mat3 mat3_pixel; 
		Mat5 mat5_pixel; 				
		/* TODO: Replace with function call to copy border pixels of width 1 */
		memcpy(dst, src, width*height);

		switch(size)
		{
		case 3:
			for(x = 1; x < height - 1; x++)
			{
				for(y = 1; y < width - 1; y++)
				{
					Populate_PixelMat3(x, y, width, src, mat3_pixel);
					ret_m3 = Get_MedianM3(mat3_pixel);							
					*(dst + x*width + y) = ret_m3;
				}
			}
			break;
		
		case 5:
			for(x = 2; x < height - 2; x++)
			{
				for(y = 2; y < width - 2; y++)
				{
					Populate_PixelMat5(x, y, width, src, mat5_pixel);
					ret_m5 = Get_MedianM5(mat5_pixel);							
					*(dst + x*width + y) = ret_m5;
				}
			}
			break;

		default:
			printf("Please mention matrix size.\n");
			break;
		}
	}
	else
	{
		printf("Invalid input parameters provided.\n");
	}
	
}/* End of function MedianFilter */


/*==============================[  End of File  ]========================================*/
