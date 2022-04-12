/**
 * @file Common_PiCam.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation of common utility functions </b> 
 * @version 
 * @date 2022-03-27 Initial template for common utilities
 * @date 2022-04-02 Update validate function for ValidateValue
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/

#include <stddef.h>
#include <stdio.h>
#include "Common_PiCam.h"

/*===========================[  Function definitions  ]===================================*/

/** \addtogroup interface_functions Interface Functions	  
 *  @{
 */

Std_ReturnType ValidateParam(void* Param)
{
    Std_ReturnType lreturn = E_NOT_OK;

    if( NULL != Param )
        lreturn = E_OK;
    
    return lreturn;

}/** End of function ValidateParam */

Std_ReturnType ValidateValue(float value, int Min, int Max)
{
    Std_ReturnType lreturn = E_NOT_OK;

    if( Min <= value && Max >= value )
        lreturn = E_OK;
    
    return lreturn;

}/** End of function ValidateParam */


Std_ReturnType ValidateImageSize(int width, int height)
{
    Std_ReturnType lreturn = E_NOT_OK;

    if( (0 == (width%2)) && (0 == (height%2)) )
        lreturn = E_OK;
    else if ((width == 0) || (height == 0))
        lreturn = E_NOT_OK;
    else
        lreturn = E_OK;

    return lreturn;
    
}/** End of function ValidateImageSize */

/** @} */

/*==============================[  End of File  ]===========================================*/
