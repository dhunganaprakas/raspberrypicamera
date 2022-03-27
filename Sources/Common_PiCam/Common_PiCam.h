/**
 * @file Common_PiCam.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for common utility functions </b>
 * @version 
 * @date 2022-03-27 Initial template for common utilities
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef COMMON_PICAM_H
#define  COMMON_PICAM_H

/*============================[  Defines  ]=============================================*/

/** Macro to indicate function returned with expected operation */
#define E_OK        (0u)

/** Macro to indicate function returned with unexpected operation */
#define E_NOT_OK    (1u)

/** Type definition for standard return type values to integer */
typedef int Std_ReturnType;

/*===========================[  Function declarations  ]=================================*/

/**
 * @brief Function to validate if the image pointer is not a NULL_PTR
 * 
 * @param[in] Param 
 * @return Std_ReturnType   Validation status
 * @retval E_OK     Validation successful
 * @retval E_NOT_OK Validation unsuccessful
 * 
 */
Std_ReturnType ValidateParam(void* Param);

/**
 * @brief Function to validate if the image size is an even number
 * 
 * @param[in] width     Width of the image
 * @param[in] height    Height of the image
 * @return Std_ReturnType   Validation status 
 * @retval E_OK     Validation successful
 * @retval E_NOT_OK Validation unsuccessful
 * 
 */
Std_ReturnType ValidateImageSize(int width, int height);

#endif /** COMMON_PICAM_H **/

/*==============================[  End of File  ]=======================================*/
