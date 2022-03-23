/**
 * @file Convolutions.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Source for implementation of convolution methods </b>
 * @version 
 * @date 2022-03-06 Initial template
 * @date 2033-03-23 Updates for Gaussian filter and Edge detection
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
 * 
 */ 
void GaussianFilter(int width, int height, unsigned char* src, unsigned char* dst)
{
    int x, y, i, j, row, column,temp,position,pixel;
	double printed = 0;

	memcpy(dst,src, width*height);

    for(x = 1; x < height -1 ; x++)
    {
		for(y = 1; y < width -1 ; y++)
        {					
            unsigned char mat_pixel[3][3];
            double blur_pixel = 0;

			for(i = 0 ; i < 3 ; i++)
            {
				for(j = 0 ; j < 3 ; j++)
                {
					position = (x - 1 + i)*width + (y - 1 + j);
					mat_pixel[i][j] =  *(src + position);
					//printf("pixel value : %d \n", mat_pixel[i][j]);
				}
			}			
			for(row = 0;row < 3;row++)
            {					
				for(column = 0;column < 3;column++)
                {
					for(temp = 0;temp < 3;temp++)
                    {				
						blur_pixel += ((double)Kernel_Gaussian[row][temp] * mat_pixel[temp][column]) ;	
						//printf("Adding %f \n", blur_pixel);	
					}												
				}
			}				
			
			pixel = LIMITCHAR((int)(blur_pixel/3));		
			//printf("before %f after %d \n",blur_pixel, pixel);
			position = x*width + y;			
			*(dst+position) = pixel;
		}
	}		

}/* End of function GaussianFilter */

/**
 * 
 */ 
void Edge_Detector(int width, int height, unsigned char* src, unsigned char* dst, EdgeDetector method)
{
	int x, y;
	for(x = 1; x < height - 1; x++)
	{
		for(y = 1; y < width - 1; y++)
		{
			int Gx = 0;
			int Gy = 0;
			int sum_x = 0;
			int sum_y = 0;
			int position;
			unsigned int intensity = 0;
	
			char mat_pixel[3][3];			
			for(int i = 0 ; i < 3 ; i++)
			{
				for(int j = 0 ; j < 3 ; j++)
				{
					position = (x - 1 + i)*width + (y - 1 + j);
					mat_pixel[i][j] =  *(src + position);
				}
			}	

			for(int row = 0;row<3;row++)
			{
				for(int column = 0;column<3;column++)
				{
					for(int temp = 0;temp<3;temp++)
					{			
						sum_x += Kernel_H_Edge[row][temp] * mat_pixel[temp][column] ;
						sum_y += Kernel_V_Edge[row][temp] * mat_pixel[temp][column] ;
					}						
				}
			}
			Gx = sum_x/9;
			Gy = sum_y/9;
			unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
			LIMITCHAR(length);								

			position = x*width + y;
			switch ( method)
			{
				case METHOD_CANNY:
					if ((length > LOWER_LIMIT_CANNY) && (length < UPPER_LIMIT_CANNY))
						*(dst + position) = 255;
					break;

				case METHOD_SOBEL:
					if ( length > LIMIT_SOBEL)
						*(dst + position) = 255;
					break;

				case METHOD_INVALID:
					printf("Invalid method provided for edge detection.\n");
					break;
			}
		}
	}

}/* End of function Edge_Detector */


/*==============================[  End of File  ]========================================*/
