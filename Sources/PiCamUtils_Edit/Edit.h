/**
 * @file Edit.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for editing functionalities </b>
 * @version 
 * @date 2022-03-28 Initial template
 * @date 2022-04-02 Update scaling, resizing and flip operations
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*===========================[  Compile Flags  ]========================================*/

#ifndef EDIT_H
#define  EDIT_H

/*===========================[  Inclusions  ]===========================================*/

#include "Common_PiCam.h"

/*============================[  Defines  ]=============================================*/


/*============================[  Data Types  ]==========================================*/

typedef struct
{
    /** Width of source image */
    int width;
    /** Hight of source image */
    int height;
    /** Rotation angle in radians */
    double rad;
} Rotate_Positions;


typedef struct
{
    /** Width of source image */
    int width;
    /** Hight of source image */
    int height;
    /** Width of output image */
    int opwidth;
    /** Height of output image */
    int opheight;
} Interpolate_Positions;


typedef struct
{
    /** Width of source image */
    int width;
    /** Hight of source image */
    int height;
    /** Pointer to starting pixel position */
    unsigned char *  start;
} Resized_Image;

/*===========================[  Function declarations  ]================================*/

/**
 * @brief   Function to populate destination image pixel values using rotation parameters and 
 *          formulas from source image. Rotation is carried out from center of the image and is 
 *          a default setting.
 * 
 * @param inPos Rotation positions required to perform rotation of Struct Rotate_Positions
 * @param src   Pointer to starting pixel position of source image
 * @param dst   Pointer to starting pixel position of destination image
 * 
 */
static inline void Copy_Pixels(Rotate_Positions inPos, unsigned char* src, unsigned char* dst);


/**
 * @brief   Function to populate the rotated images using averaging technique from pixel at 
 *          positions-up, down, left and right adjacent to the blank pixel.
 * 
 * @param width     Width of image
 * @param height    Hight of image
 * @param dst       Pointer to starting pixel position of destination image
 * 
 */
static inline void Fill_Gaps(int width, int height, unsigned char* dst);

/**
 * @brief   Performs horizontal rotation of 180 degrees using the height as the axis of rotation. 
 *          Mirror image at horizontal direction is created.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image
 * @param dst       Pointer to starting pixel position of destination image
 * 
 */
static inline void HFlip(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief   Performs vertical rotation of 180 degrees using the width as the axis of rotation. 
 *          Mirror image at horizontal direction is created.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image
 * @param dst       Pointer to starting pixel position of destination image
 * 
 */
static inline void VFlip(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param inPos Source and destination image sizes required to perform interpolation
 * @param src   Pointer to starting pixel position of source image 
 * @param dst   Pointer to starting pixel position of destination image 
 * 
 */
static inline void Interpolate_Scale(Interpolate_Positions inPos, unsigned char* src, unsigned char* dst);

/**
 * @brief   Function to perform rotation of an image.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image 
 * @param dst       Pointer to starting pixel position of destination image 
 * @param angle 
 * 
 * @return Std_ReturnType   Operation Status
 * @retval E_OK             Operation successful
 * @retval E_NOT_OK         Operation unsuccessful
 * 
 */
Std_ReturnType Rotate_Image(int width, int height, unsigned char* src, unsigned char* dst, int angle);

/**
 * @brief   Function to perform horizontal flip of an image.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image 
 * @param dst       Pointer to starting pixel position of destination image 
 * 
 * @return Std_ReturnType   Operation Status
 * @retval E_OK             Operation successful
 * @retval E_NOT_OK         Operation unsuccessful
 * 
 */
Std_ReturnType HorizontalFlip(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief   Function to perform vertical flip of an image.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image 
 * @param dst       Pointer to starting pixel position of destination image  
 * 
 * @return Std_ReturnType   Operation Status
 * @retval E_OK             Operation successful
 * @retval E_NOT_OK         Operation unsuccessful
 * 
 */
Std_ReturnType VerticalFlip(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief   Function to perform upscale and downscale operation in an image.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image 
 * @param factor    Upscale/Downscale factor to apply in the source image
 * 
 * @return Std_ReturnType   Up-scaled Image if factor > 1 else Down-scaled Image
 * 
 */
Resized_Image ScaleImage(int width, int height, unsigned char* src, float factor);

/**
 * @brief   Function to perform resize of an image.
 * 
 * @param width     Width of source image
 * @param height    Hight of source image
 * @param src       Pointer to starting pixel position of source image  
 * @param newWidth  Width of destination image
 * @param newHeight Hight of destination image 
 * 
 * @return Resized_Image    Resized Image 
 * 
 */
Resized_Image ResizeImage(int width, int height, unsigned char* src, int newWidth, int newHeight);

#endif /* EDIT_H */

/*==============================[  End of File  ]======================================*/
