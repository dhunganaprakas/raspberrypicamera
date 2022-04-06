/**
 * @file Edit.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation of editing functions </b>
 * @version
 * @date 2022-03-28 Initial template
 * @date 2022-04-02 Update scaling, resizing and flip operations
 * @date 2022-04-03 Update editing functions
 * @date 2022-04-05 Update editing functions for RGB colorspace
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

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src and dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void Copy_Pixels(Rotate_Positions inPos, unsigned char* src, unsigned char* dst)
{
    int VC = inPos.height/2;
    int HC = inPos.width/2;
    int x, y;
    int pos;

    for (x = 0; x < inPos.width; ++x) 
    {
        for (y = 0; y < inPos.height; ++y) 
        {
            float VP = (float) cos(inPos.rad)*(y - VC)+sin(inPos.rad)*(x - HC) + VC;
            float HP = (float) -sin(inPos.rad)*(y - VC)+cos(inPos.rad)*(x - HC) + HC;
                
            if (VP >= 0 && VP < inPos.height && HP >= 0 && HP < inPos.width)
            {
                pos = 3*((int)VP * inPos.width + (int)HP);

                *(dst + pos) = *(src + 3*y * inPos.width + 3*x);
                *(dst + pos + 1) = *(src + 3*y * inPos.width + 3*x + 1);
                *(dst + pos + 2) = *(src + 3*y * inPos.width + 3*x + 2);       
            }
        }
    }
}


/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void Fill_Gaps(int width, int height, unsigned char* dst)
{
    int x, y;
    unsigned char UP, DOWN, LEFT, RIGHT;
    int pos_up, pos_down, pos_left, pos_right, pos; 

    for (x = 1; x < width -1 ; ++x)
    {
        for (y = 1; y < height- 1 ; ++y)
        {
            unsigned char pixel = *(dst + 3* (y * width + x));	    
            if(0 == pixel)
            {
                pos_up = 3*((y-1) * width + x);
                pos_down = 3*((y+1) * width + x);
                pos_left = 3*(y*width + x - 1);
                pos_right = 3*(y*width + x + 1);
                pos = 3*(y * width + x);

                UP = *(dst + pos_up);			
                DOWN = *(dst + pos_down);
                LEFT = *(dst + pos_left);
                RIGHT = *(dst + pos_right);			
                *(dst + pos) = ((UP + DOWN + LEFT + RIGHT) >> 2);

                UP = *(dst + pos_up + 1);			
                DOWN = *(dst + pos_down + 1);
                LEFT = *(dst + pos_left + 1);
                RIGHT = *(dst + pos_right + 1);			
                *(dst + pos + 1) = ((UP + DOWN + LEFT + RIGHT) >> 2);

                UP = *(dst + pos_up + 2);			
                DOWN = *(dst + pos_down + 2);
                LEFT = *(dst + pos_left + 2);
                RIGHT = *(dst + pos_right + 2);			
                *(dst + pos + 2) = ((UP + DOWN + LEFT + RIGHT) >> 2);				
            }  	    	 
        }
    }
}

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src and dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void HFlip(int width, int height, unsigned char* src, unsigned char* dst)
{
    int x, y, src_pos, dst_pos;

    for (x = 0; x < width ; ++x)
    {
        for (y = 0; y < height ; ++y)
        {
            src_pos = 3 * (y * width + x);
            dst_pos = 3 * (y * width + width - x);
			
            *(dst + dst_pos) = *(src + src_pos);
            *(dst + dst_pos + 1) = *(src + src_pos + 1);
            *(dst + dst_pos + 2) = *(src + src_pos + 2);				   	 
        }
    }
}

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src and dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void VFlip(int width, int height, unsigned char* src, unsigned char* dst)
{
    int x, y, src_pos, dst_pos;

    for (x = 0; x < width ; ++x)
    {
        for (y = 0; y < height ; ++y)
        {
            src_pos = 3 * (y * width + x);
            dst_pos = 3 * ((height - y) * width + x);
			
            *(dst + dst_pos) = *(src + src_pos);
            *(dst + dst_pos + 1) = *(src + src_pos + 1);
            *(dst + dst_pos + 2) = *(src + src_pos + 2);				   	 
        }
    }
}

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src and dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
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
            offset = rowoffset*inPos.width*3 + coloffset*3;

            *(dst + 3*x * inPos.opwidth + y*3 ) = *(src + offset);
            *(dst + 3*x * inPos.opwidth + y*3 + 1) = *(src + offset + 1);
            *(dst + 3*x * inPos.opwidth + y*3 + 2) = *(src + offset + 2);
        }
    }
}

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src and dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void BLT(int width, int height, unsigned char* src, unsigned char* dst, float gain, float bias)
{
    int x, y, offset;

    for (x = 0; x < height ; ++x)
    {
        for (y = 0; y < width ; ++y)
        {
            offset = 3*(x * width + y);         

            *(dst + offset) = LIMITPIXEL(*(src + offset) * gain + bias);
            *(dst + offset + 1) = LIMITPIXEL(*(src + offset +1) * gain + bias);
            *(dst + offset + 2) = LIMITPIXEL(*(src + offset +2) * gain + bias);
        }
    }
}

/**
 * @note This function assumes the provided pointer for source image pixel data is not a NULL_PTR.
 * @warning NULL_PTR should not be passed to this function in place of src and dst, if NULL_PTR is passed,
 * 			the function doesnot have a sanity check and results in segmentation faults.
 * 
 */
static inline void TransformConstrast(int width, int height, unsigned char* src, unsigned char* dst, float ratio)
{
    int x, y, offset;

    for (x = 0; x < height ; ++x)
    {
        for (y = 0; y < width ; ++y)
        {
            offset = 3*(x * width + y);         

            *(dst + offset) = LIMITPIXEL((float)ratio * (*(src + offset)));
            *(dst + offset + 1) = LIMITPIXEL((float)ratio * (*(src + offset + 1)));
            *(dst + offset + 2) = LIMITPIXEL((float)ratio * (*(src + offset + 2)));
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
        int size = width*height;
        do{
            *(dst + 3*size + 1) = 128;
            *(dst + 3*size + 2) = 128;
            size--;
        }while(size >= 0);

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
    dst.start = (unsigned char*) malloc(newWidth*newHeight*3);

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
    dst.start = (unsigned char*) malloc(newWidth*newHeight*3);

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


Std_ReturnType ContrastEnhancement_BLT(int width, int height, unsigned char* src, unsigned char* dst, float gain, float bias)
{
    Std_ReturnType lreturn = E_OK; 

	lreturn += ValidateParam(src);
	lreturn += ValidateImageSize(width, height);
    lreturn += ValidateValue(gain, 1, 3);
    lreturn += ValidateValue(bias, 0, 10);

	if (E_OK == lreturn)
	{
        BLT(width, height, src, dst, gain, bias); 
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }

    return lreturn;

}/* End of function ContrastEnhancement_BLT */


Std_ReturnType ContrastEnhancement_Percent(int width, int height, unsigned char* src, unsigned char* dst, int percent)
{
    Std_ReturnType lreturn = E_OK; 
    float ratio;

	lreturn += ValidateParam(src);
	lreturn += ValidateImageSize(width, height);
    lreturn += ValidateValue(percent, 1, 100);

	if (E_OK == lreturn)
	{       
        ratio = (float)(100 + percent)/100;
        TransformConstrast(width, height, src, dst, ratio); 
    }
    else
    {
        printf("Invalid input parameters provided.\n");
    }

    return lreturn;

}/* End of function ContrastEnhancement_Percent */


/*==============================[  End of File  ]========================================*/
