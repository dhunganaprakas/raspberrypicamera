/**
 * @file Edit.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for editing functionalities </b>
 * @version 
 * @date 2022-03-28 Initial template
 * @date 2022-04-02 Update scaling, resizing and flip operations
 * @date 2022-04-05 Update editing functions
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

/** \addtogroup data_types	  
 *  @{
 */

/** Structure to store informations required to perform rotation of an image */
typedef struct
{
    /** Width of source image */
    int width;
    /** Hight of source image */
    int height;
    /** Rotation angle in radians */
    double rad;
} Rotate_Positions;

/** Structure to store informations required to perform interpolation of image for resizing
 *  and scaling operations 
 */
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

/**
 * Structure to store resized image after resizing and scaling operations 
 */
typedef struct
{
    /** Width of source image */
    int width;
    /** Hight of source image */
    int height;
    /** Pointer to starting pixel position */
    unsigned char *  start;
} Resized_Image;

/** @} */

/*===========================[  Function declarations  ]================================*/

/** \addtogroup internal_functions Internal Functions	  
 *  @{
 */

/**
 * @brief   Function to populate destination image pixel values using rotation parameters and 
 *          formulas from source image. Rotation is carried out from center of the image and is 
 *          a default setting.
 * 
 * @param[in] inPos     Rotation positions required to perform rotation of Struct Rotate_Positions
 * @param[in] src       Pointer to starting pixel position of source image
 * @param[inout] dst    Pointer to starting pixel position of destination image
 * 
 */
static inline void Copy_Pixels(Rotate_Positions inPos, unsigned char* src, unsigned char* dst);


/**
 * @brief   Function to populate the rotated images using averaging technique from pixel at 
 *          positions-up, down, left and right adjacent to the blank pixel.
 * 
 * @param[in] width     Width of image
 * @param[in] height    Hight of image
 * @param[inout] dst    Pointer to starting pixel position of destination image
 * 
 */
static inline void Fill_Gaps(int width, int height, unsigned char* dst);


/**
 * @brief   Performs horizontal rotation of 180 degrees using the height as the axis of rotation. 
 *          Mirror image at horizontal direction is created.
 * 
 * @param[in] width     Width of source image
 * @param[in] height    Hight of source image
 * @param[in] src       Pointer to starting pixel position of source image
 * @param[inout] dst    Pointer to starting pixel position of destination image
 * 
 */
static inline void HFlip(int width, int height, unsigned char* src, unsigned char* dst);


/**
 * @brief   Performs vertical rotation of 180 degrees using the width as the axis of rotation. 
 *          Mirror image at horizontal direction is created.
 * 
 * @param[in] width     Width of source image
 * @param[in] height    Hight of source image
 * @param[in] src       Pointer to starting pixel position of source image
 * @param[inout] dst    Pointer to starting pixel position of destination image
 * 
 */
static inline void VFlip(int width, int height, unsigned char* src, unsigned char* dst);


/**
 * @brief   Helper function to perform interpolation of pixel position to copy pixel value to 
 *          nearest neighbour pixel location.
 * 
 * @param[in] inPos     Source and destination image sizes required to perform interpolation
 * @param[in] src       Pointer to starting pixel position of source image 
 * @param[inout] dst    Pointer to starting pixel position of destination image 
 * 
 */
static inline void Interpolate_Scale(Interpolate_Positions inPos, unsigned char* src, unsigned char* dst);


/**
 * @brief Helper function to transform contrast of an image during basic linear transformation (BLT).
 * 
 * @param[in] width     Width of source image
 * @param[in] height    Hight of source image
 * @param[in] src       Pointer to starting pixel position of source image 
 * @param[inout] dst    Pointer to starting pixel position of destination image 
 * @param[in] gain 
 * @param[in] bias 
 * 
 */
static inline void BLT(int width, int height, unsigned char* src, unsigned char* dst, float gain, float bias);


/**
 * @brief Helper function to transform contrast of an image during percentage increment.
 * 
 * @param[in] width     Width of source image
 * @param[in] height    Hight of source image
 * @param[in] src       Pointer to starting pixel position of source image 
 * @param[inout] dst    Pointer to starting pixel position of destination image  
 * @param[in] ratio     Ratio for contrast transformation
 * 
 */
static inline void TransformConstrast(int width, int height, unsigned char* src, unsigned char* dst, float ratio);

/** @} */

/** \addtogroup interface_functions Interface Functions	  
 *  @{
 */

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


/**
 * @brief Enhance contrast of an image using basic linear transformation (BLT).
 * 
 * @param[in] width     Width of source image
 * @param[in] height    Height of source image
 * @param[in] src       Pointer to starting pixel position of source image  
 * @param[inout] dst    Pointer to starting pixel position of destination image  
 * @param[in] gain      Gain value for BLT
 * @param[in] bias      Bias value for BLT
 * 
 * @return Std_ReturnType   Operation Status
 * @retval E_OK             Operation successful
 * @retval E_NOT_OK         Operation unsuccessful 
 * 
 */
Std_ReturnType ContrastEnhancement_BLT(int width, int height, unsigned char* src, unsigned char* dst, float gain, float bias);


/**
 * @brief Enhance contrast of an image using percentage increment.
 * 
 * @param[in] width     Width of source image
 * @param[in] height    Height of source image
 * @param[in] src       Pointer to starting pixel position of source image 
 * @param[inout] dst    Pointer to starting pixel position of destination image  
 * @param[in] percent   Percent value to increase contrast of the source image
 * 
 * @return Std_ReturnType   Operation Status
 * @retval E_OK             Operation successful
 * @retval E_NOT_OK         Operation unsuccessful 
 * 
 */
Std_ReturnType ContrastEnhancement_Percent(int width, int height, unsigned char* src, unsigned char* dst, int percent);

/** @} */

#endif /* EDIT_H */

/*==============================[  End of File  ]======================================*/
