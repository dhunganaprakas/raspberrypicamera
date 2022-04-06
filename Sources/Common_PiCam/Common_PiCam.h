/**
 * @file Common_PiCam.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for common utility functions </b>
 * @version 
 * @date 2022-03-27 Initial template for common utilities
 * @date 2022-04-02 Update validate function for ValidateValue
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef COMMON_PICAM_H
#define  COMMON_PICAM_H

/*===========================[  Inclusions  ]============================================*/

#include <sys/time.h>

/*============================[  Defines  ]==============================================*/

/** Macro to indicate function returned with expected operation */
#define E_OK        (0u)

/** Macro to indicate function returned with unexpected operation */
#define E_NOT_OK    (1u)

/** Prevent overflow of pixel value */
#define LIMITPIXEL(x) ((x>255)?255:((x<0)?0:x))

/*============================[  DAta Types  ]=========================================*/

/** Type definition for standard return type values to integer */
typedef int Std_ReturnType;

struct buffer {
    /** Pointer to starting pixel position */
    unsigned char *  start;
    /** Pixel buffer length */
    size_t  length;
    /** Timestamp of captured image buffer */
    struct timeval timestamp;
};

/*============================[  Global Variables  ]=====================================*/

/** Flag to store information whether ti capture continuous frame or not */
int continuous;

/** Global buffer to store the image to implement desired algorithms and to save it */
struct buffer Image_Buffer;

/*===========================[  Function declarations  ]=================================*/

/**
 * @brief Function to validate input parameter value is within range of Min and Max values. 
 * 
 * @param value Value to validate
 * @param Min   Minimum acceptable value of input param value
 * @param Max   Maximum acceptable value of input param value
 * 
 * @return Std_ReturnType   Validation Status
 * @retval E_OK             Validation successful
 * @retval E_NOT_OK         Validation unsuccessful
 * 
 */
Std_ReturnType ValidateValue(float value, int Min, int Max);

/**
 * @brief Function to validate if the image pointer is not a NULL_PTR.
 * 
 * @param[in] Param 
 * 
 * @return Std_ReturnType   Validation Status
 * @retval E_OK             Validation successful
 * @retval E_NOT_OK         Validation unsuccessful
 * 
 */
Std_ReturnType ValidateParam(void* Param);

/**
 * @brief Function to validate if the image size is an even number.
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * 
 * @return Std_ReturnType   Validation Status
 * @retval E_OK             Validation successful
 * @retval E_NOT_OK         Validation unsuccessful
 * 
 */
Std_ReturnType ValidateImageSize(int width, int height);

#endif /** COMMON_PICAM_H **/

/*==============================[  End of File  ]=======================================*/
