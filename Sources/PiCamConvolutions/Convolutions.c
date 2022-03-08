/**
 * @file Convolutions.c
 * @author Prakash Dhungana (dhunganaprakas)
 * @brief Source for implementation of convolution methods 
 * @version 0.0.1
 * @date 2022-03-06 Initial template
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*===========================[  Compile Flags  ]==========================================*/


/*===========================[  Inclusions  ]=============================================*/

#include "Convolutions.h"

/*===========================[ Global Variables  ]========================================*/

double Kernel_Gaussian[3][3] = { {(1/16),(1/8),(1/18)},
                                 {(1/8),(1/4),(1/8)},
                                 {(1/16),(1/8),(1/18)}                                
                                };

/*===========================[  Function definitions  ]===================================*/
/**
 * 
 */ 
void GaussianFilter(int width, int height, const unsigned char* src, unsigned char* dst)
{
    int x, y, i, j, row, column;
    /* Update the destination pointer */
    dst = (dst + width + 1);

    for(x = 1; x< (width - 1); x++)
    {
		for(y = 1; y < (height - 1); y++)
        {					
			char * pixel;
            int mat_pixel[3][3];
            double blur_pixel;

			for(i = 0 ; i < 3 ; i++)
            {
				for(j = 0 ; j < 3 ; j++)
                {
					mat_pixel[i][j] = *(src  + (x - 1 + i)*width + (y - 1 + j));
				}
			}			
			for(int row = 0;row<5;row++)
            {					
				for(int column = 0;column<5;column++)
                {
					for(int temp = 0;temp<5;temp++)
                    {				
						blur_pixel += Kernel_Gaussian[row][temp] * mat_pixel[temp][column] ;		
					}												
				}
			}				
			blur_pixel = (blur_pixel / 9);					
			*(dst++) = blur_pixel;
		}
	}		


}/* End of function GaussianFilter */

/**
 * 
 */ 
void CannyEdge_Detector(int width, int height, const unsigned char* src, unsigned char* dst)
{

}/* End of function CannyEdge_Detector */

/**
 * 
 */ 
void SobelEdge_Detector(int width, int height, const unsigned char* src, unsigned char* dst)
{

}/* End of function SobelEdge_Detector */

/*==============================[  End of File  ]========================================*/
