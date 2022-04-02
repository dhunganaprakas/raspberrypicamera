/**
 * @file Edit.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation of editing functions </b>
 * @version
 * @date 2022-03-28 Initial template
 * @date 2022-04-02 Update scaling, resizing and flip operations
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
#include "Edit.h"

/*===========================[ Global Variables  ]========================================*/



/*===========================[  Function definitions  ]===================================*/

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

static inline void HFlip(int width, int height, unsigned char* src, unsigned char* dst)
{
    int x, y, src_pos, dst_pos;

    for (x = 0; x < width ; ++x)
    {
        for (y = 0; y < height ; ++y)
        {
            src_pos = y * width + x;
            dst_pos = y * width + width - x;
			
            *(dst + dst_pos) = *(src + src_pos);				   	 
        }
    }
}

static inline void VFlip(int width, int height, unsigned char* src, unsigned char* dst)
{
    int x, y, src_pos, dst_pos;

    for (x = 0; x < width ; ++x)
    {
        for (y = 0; y < height ; ++y)
        {
            src_pos = y * width + x;
            dst_pos = (height - y) * width + x;
			
            *(dst + dst_pos) = *(src + src_pos);				   	 
        }
    }

}

/**
 * 
 * 
 */
static inline void Interpolate_Scale(Interpolate_Positions inPos, unsigned char* src, unsigned char* dst)
{
    int x, y, offset, rowoffset, coloffset;

    for (x = 0; x < inPos.opheight ; ++x)
    {
        rowoffset = (int)(x * inPos.height) / inPos.opheight;
        for (y = 0; y < inPos.opwidth ; ++y)
        {
            coloffset = (int)(y*inPos.width)/inPos.opwidth;
            offset = rowoffset*inPos.width + coloffset;

            *(dst + x * inPos.opwidth + y) = *(src + offset);
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
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
	{
        HFlip(width, height, src, dst);
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }
    
    return validate;

}/* End of function HorizontalFlip */


/** 
 * 
 */
Std_ReturnType VerticalFlip(int width, int height, unsigned char* src, unsigned char* dst)
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

	if (E_OK == validate)
	{
        VFlip(width, height, src, dst);
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }
    
    return validate;

}/* End of function VerticalFlip */


/** 
 * 
 */
Resized_Image ScaleImage(int width, int height, unsigned char* src, float factor)
{
    Std_ReturnType validate = E_OK;
    int newWidth = (int) width*factor;
    int newHeight = (int) height*factor;    
    Resized_Image dst;
    int fill = 0;

	validate += ValidateParam(src);
	validate += ValidateImageSize(width, height);
    validate += ValidateValue(factor, 0, 5);
    dst.width = newWidth;
    dst.height = newHeight;
    dst.start = (unsigned char*) malloc(newWidth*newHeight);

    validate += ValidateParam(dst.start);

	if (E_OK == validate)
	{       
        Interpolate_Positions lData = { width, height, newWidth, newHeight};        
        Interpolate_Scale(lData, src, dst.start);
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }

    return dst;

}/* End of function ScaleImage */

Resized_Image ResizeImage(int width, int height, unsigned char* src, int newWidth, int newHeight)
{
    Std_ReturnType validate = E_OK; 
    Resized_Image dst;

	validate += ValidateParam(src);
	validate += ValidateImageSize(width, height);
    validate += ValidateImageSize(newWidth, newHeight);
    dst.width = newWidth;
    dst.height = newHeight;
    dst.start = (unsigned char*) malloc(newWidth*newHeight);

    validate += ValidateParam(dst.start);

	if (E_OK == validate)
	{       
        Interpolate_Positions lData = { width, height, newWidth, newHeight};        
        Interpolate_Scale(lData, src, dst.start);
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }

    return dst;

}/* End of function ResizeImage */



/*==============================[  End of File  ]========================================*/
