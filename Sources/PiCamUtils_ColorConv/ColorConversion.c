/**
 * @file ColorConversion.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation for color-space conversion functions </b>
 * @version 
 * @date 2022-03-03 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2022-03-28 Rename and move to appropriate folder
 * @date 2022-04-03 Update color conversion functions for HSV
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "write.h"
#include "ColorConversion.h"

/*===========================[  Function definitions  ]===================================*/

/** \addtogroup interface_functions Interface Functions	  
 *  @{
 */

/**
 * In this format each four bytes is two pixels in YUV colorspace. Each four bytes has 
 * two Luminance(Y), and single Chrominances namely Chroma Blue(Cb) and Chroma Red(Cr).
 * Each Y goes to one of the pixels, and the Cb and Cr belong to both pixels. 
 * 
 */
void Convert_YUV420toYUV444(int width, int height, unsigned char* src, unsigned char* dst) 
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

    /** Sanity check for input parameters */
    if (E_OK == validate)
    {
        int row, column;
        int frame = width * height;
        int chroma_length = frame / 4;
        
		for (row = 0; row < height ; row++ ) 
        {
			for (column = 0; column < width ; column++ ) 
            {
				int pos = row * width + column;
                int chroma_pos = ((int)(row/2) * (int)(width/2)) + (column/2);

                /** Luminance value update */
                *(dst++) = *(src + pos);
                /** Chrominance values update */
                *(dst++) = *(src + frame + chroma_pos);
                *(dst++) = *(src + frame + chroma_length + chroma_pos);
			}
		}
    }
    else
    {
        errno_exit("YUV420 to YUV444 Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_YUV420toYUV444 */


void Convert_YUV420toBMPRGB(int width, int height, unsigned char* src, unsigned char* dst) 
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

    /** Sanity check for input parameters */
    if (E_OK == validate)
    {
        int row, column;
        int frame = width * height;
        int chroma_length = frame / 4;
        int pixel_Y, pixel_U, pixel_V;
        int dst_position;
        
		for (row = height -1; row >= 0 ; row-- ) 
        {
			for (column = width -1; column >= 0 ; column-- ) 
            {
				int pos = row * width + column;
                int chroma_pos = ((int)(row/2) * (int)(width/2)) + (column/2);

                /** Luminance value update */
                pixel_Y = *(src + pos);
                /** Chrominance values update */
                pixel_V = *(src + frame + chroma_pos);
                pixel_U = *(src + frame + chroma_length + chroma_pos);

                /** Luminance value update */
                *(dst++) = GETREDPIXEL_FROM_YUV(pixel_Y, pixel_V);  
                *(dst++) = GETGREENPIXEL_FROM_YUV(pixel_Y, pixel_U, pixel_V);
                *(dst++) = GETBLUEPIXEL_FROM_YUV(pixel_Y, pixel_U);            
                
			}
		}
    }
    else
    {
        errno_exit("YUV420 to RGB Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_YUV420toBMPRGB */

void Convert_YUV444toRGB444(int width, int height, unsigned char* src, unsigned char* dst) 
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

    /** Sanity check for input parameters */
    if (E_OK == validate)
    {
        int row, column;
        int frame = width * height;
        int chroma_length = frame / 4;
        int pixel_Y, pixel_U, pixel_V;
        int dst_position;
        
		for (row = 0; row < height ; row++ ) 
        {
			for (column = 0; column < width ; column++ ) 
            {
				int pos = 3*(row * width + column);

                /** Luminance value update */
                pixel_Y = *(src + pos);
                /** Chrominance values update */
                pixel_U = *(src + pos + 1);
                pixel_V = *(src + pos + 2);

                /** Luminance value update */
                *(dst++) = GETREDPIXEL_FROM_YUV(pixel_Y, pixel_V);  
                *(dst++) = GETGREENPIXEL_FROM_YUV(pixel_Y, pixel_U, pixel_V);
                *(dst++) = GETBLUEPIXEL_FROM_YUV(pixel_Y, pixel_U);            
                
			}
		}
    }
    else
    {
        errno_exit("YUV420 to RGB Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_YUV444toRGB444 */

/** TODO: Implementation is not correct. Redo whole function */
void Convert_RGB444toHSV444(int width, int height, unsigned char* src, u_int16_t* dst)
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

    /** Sanity check for input parameters */
    if (E_OK == validate)
    {
        int x, y, offset;
        double r, g, b, pmax, pmin;
        int h, s, diff, v;

	    for(x = 0; x < width ; x++)
        {
		    for(y = 0; y < height ; y++)
            {				
                offset = 3*(y * width + x);												
                r = *(src + offset)/255;
                g = *(src + offset + 1)/255;
                b = *(src + offset + 2)/255;

                pmax = (r > g ? r : (g > b ? g : b));
			    pmin = (r < g ? r : (g < b ? g : b));
			    diff = pmax - pmin;

			    if(pmax == 0)
			    	s = 0;
			    else
				    s =(diff/pmax)*100;	

                v = pmax;

                if(diff == 0)
                    h = 0;
                else if(pmax == r)
                    h = (int)(60 * (abs(g-b)/diff) + 360) % 360;
                else if(pmax == g)
                    h = (int)(60 * (abs(b-r)/diff) + 120) % 360;
                else if(pmax == b)
                    h = (int)(60 * (abs(r-g)/diff) + 240) % 360;

                *(dst + offset*sizeof(u_int16_t)) = h; 
                *(dst + offset*sizeof(u_int16_t) + sizeof(u_int16_t)) = s;
                *(dst + offset*sizeof(u_int16_t) + 2*sizeof(u_int16_t)) = v;		
		    }
	    }
    }
    else
    {
        errno_exit("YUV420 to RGB Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_RGB444toHSV444 */

/** TODO: Implementation is not correct. Redo whole function */
void Convert_HSV444toRGB444(int width, int height, u_int16_t* src, unsigned char* dst)
{
    Std_ReturnType validate = E_OK;

	validate += ValidateParam(src);
	validate += ValidateParam(dst);
	validate += ValidateImageSize(width, height);

    /** Sanity check for input parameters */
    if (E_OK == validate)
    {
        int row, col, offset, rp, gp, bp;
        int h, s, pmax, pmin, diff, v;
        int c, x, m, mod;
        
		for (row = 0; row < height ; row++ ) 
        {
			for (col = 0; col < width ; col++ ) 
            {
                offset = 3*(row * width + col);												
                h = *(src + offset);
                s = *(src + offset + 1);
                v = *(src + offset + 2);

                c = v * s;
                mod = fabs( ((int)(h/60)%2) - 1);
                x = c * (1 - mod);
                m = v - c;

                if (0 <= h < 60)
                {
                    rp = c;
                    gp = x;
                    bp = 0;
                }
                else if (60 <= h < 120)
                {
                    rp = x;
                    gp = c;
                    bp = 0;
                }
                else if (120 <= h < 180)
                {
                    rp = 0;
                    gp = c;
                    bp = x;
                }
                else if (180 <= h < 240)
                {
                    rp = 0;
                    gp = x;
                    bp = c;
                }
                else if (240 <= h < 300)
                {
                    rp = x;
                    gp = 0;
                    bp = c;
                }
                else
                {
                    rp = c;
                    gp = 0;
                    bp = x;
                }                             
                
                *(dst++) = (rp + m)*255; 
                *(dst++) = (gp + m)*255;
                *(dst++) = (bp + m)*255;
			}
		}
    }
    else
    {
        errno_exit("YUV420 to RGB Conversion cannot be performed because of invalid input parameters\n");
    }
}/* End of function Convert_HSV444toRGB444 */

/** @} */

/*==============================[  End of File  ]======================================*/
