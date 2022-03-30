/**
 * @file Edit.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation of editing functions </b>
 * @version
 * @date 2022-03-28 Initial template
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/


/*===========================[  Inclusions  ]=============================================*/

#include <stdio.h>
#include <math.h>
#include "Edit.h"

/*===========================[ Global Variables  ]========================================*/



/*===========================[  Function definitions  ]===================================*/

static inline void Interpolate_Bilinear (Rotate_Positions inPos, unsigned char* input, unsigned char* output)
{
    int x, y;
    int VC = inPos.height/2;
    int HC = inPos.width/2;

    for (x = 0; x < inPos.width; ++x) 
    {
        for (y = 0; y < inPos.height; ++y) 
        {
            float VP = (float) cos(inPos.rad)*(y - VC)+sin(inPos.rad)*(x - HC) + VC;
            float HP = (float) -sin(inPos.rad)*(y - VC)+cos(inPos.rad)*(x - HC) + HC;

            int top = floor(VP);
            int bottom = top + 1;
            int left = floor(HP);
            int right = left + 1;

            float top_left = *(input + top*inPos.width + left);
            float top_right = *(input + top*inPos.width + right);
            float bottom_left = *(input + bottom*inPos.width + left);
            float bottom_right = *(input + bottom*inPos.width + right);

            // Figure out "how far" the output pixel being considered is between *_left and *_right.
            float HD = HP - left;
            float VD = VP - top;

            // Combine top_left and top_right into one large, horizontal block.
            int top_block = (int)(top_left + HD * (top_right - top_left));

            // Combine bottom_left and bottom_right into one large, horizontal block.
            int bottom_block = (int)(bottom_left + HD * (bottom_right - bottom_left));

            // Combine the top_block and bottom_block using vertical interpolation and return as the resulting pixel.
            if (VP >= 0 && VP < inPos.height && HP >= 0 && HP < inPos.width)
            {
                *(output + ((int)VP)*inPos.width + ((int)HP)) = top_block + ((int)VD) * (bottom_block - top_block);
            }
        }
    }
}

static inline void Copy_Pixels(Rotate_Positions inPos, unsigned char* src, unsigned char* dst)
{
    int VC = inPos.height/2;
    int HC = inPos.width/2;
    int x, y;

    for (x = 0; x < inPos.width; ++x) 
    {
        for (y = 0; y < inPos.height; ++y) 
        {
            float VP = (float) cos(inPos.rad)*(y - VC)+sin(inPos.rad)*(x - HC) + VC;
            float HP = (float) -sin(inPos.rad)*(y - VC)+cos(inPos.rad)*(x - HC) + HC;
                
            if (VP >= 0 && VP < inPos.height && HP >= 0 && HP < inPos.width)
            {
                *(dst + ((int)VP) * inPos.width + ((int)HP)) = *(src + y * inPos.width + x);       
            }
        }
    }
}


static inline void Fill_Gaps(int width, int height, unsigned char* dst)
{
    int x, y;

    for (x = 1; x < width -1 ; ++x)
    {
        for (y = 1; y < height- 1 ; ++y)
        {
            unsigned char pixel = *(dst + y * width + x);	    
            if(0 == pixel)
            {
                unsigned char UP = *(dst + (y-1) * width + x);			
                unsigned char DOWN = *(dst + (y+1) * width + x);
                unsigned char LEFT = *(dst + y*width + x - 1);
                unsigned char RIGHT = *(dst + y*width + x + 1);
                int pix = ((UP + DOWN + LEFT + RIGHT) >> 2);
			
                *(dst + y * width + x) = pix;				
            }  	    	 
        }
    }
}

/** 
 * 
 */
Std_ReturnType Rotate_Image(int width, int height, unsigned char* src, unsigned char* dst, int angle)
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
	{
        double rad = angle * (double) M_PI / 180;
        Rotate_Positions sendValue = {width, height, rad}; 
        Copy_Pixels(sendValue, src, dst);
        Fill_Gaps(width, height, dst);
        Fill_Gaps(width, height, dst);
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }
    
    return validate;
}/* End of function Rotate_Image */


/** 
 * 
 */
Std_ReturnType HorizontalFlip(int width, int height, unsigned char* src, unsigned char* dst)
{

}/* End of function HorizontalFlip */


/** 
 * 
 */
Std_ReturnType VerticalFlip(int width, int height, unsigned char* src, unsigned char* dst)
{

}/* End of function VerticalFlip */


/** 
 * 
 */
Std_ReturnType UpscaleImage_Factor(int width, int height, unsigned char* src, unsigned char* dst, int factor)
{

}/* End of function UpscaleImage_Factor */


/** 
 * 
 */
Std_ReturnType DownscaleImage_Factor(int width, int height, unsigned char* src, unsigned char* dst, int factor)
{

}/* End of function DownscaleImage_Factor */


/** 
 * 
 */
Std_ReturnType UpscaleImage_Size(int width, int height, unsigned char* src, unsigned char* dst, int newwidth, int newheight)
{

}/* End of function UpscaleImage_Size */


/** 
 * 
 */
Std_ReturnType DownscaleImage_Size(int width, int height, unsigned char* src, unsigned char* dst, int newwidth, int newheight)
{

}/* End of function DownscaleImage_Size */



/*==============================[  End of File  ]========================================*/
