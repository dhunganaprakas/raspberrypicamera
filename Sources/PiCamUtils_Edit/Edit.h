/**
 * @file Edit.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for editing functionalities </b>
 * @version 
 * @date 2022-03-28 Initial template
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


/*===========================[  Function declarations  ]================================*/

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * @param angle 
 * 
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType Rotate_Image(int width, int height, unsigned char* src, unsigned char* dst, int angle);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * 
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType HorizontalFlip(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * 
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType VerticalFlip(int width, int height, unsigned char* src, unsigned char* dst);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * @param factor 
 * 
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType UpscaleImage_Factor(int width, int height, unsigned char* src, unsigned char* dst, int factor);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * @param factor 
 * 
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType DownscaleImage_Factor(int width, int height, unsigned char* src, unsigned char* dst, int factor);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * @param newwidth 
 * @param newheight
 *  
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType UpscaleImage_Size(int width, int height, unsigned char* src, unsigned char* dst, int newwidth, int newheight);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param dst 
 * @param newwidth 
 * @param newheight
 *  
 * @return Std_ReturnType 
 * 
 */
Std_ReturnType DownscaleImage_Size(int width, int height, unsigned char* src, unsigned char* dst, int newwidth, int newheight);

#endif /* EDIT_H */

/*==============================[  End of File  ]======================================*/
