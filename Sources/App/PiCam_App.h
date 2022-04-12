/**
 * @file PiCam_App.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header file for main application </b>
 * @version 
 * @date 2022-04-06 
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]=========================================*/

#ifndef PICAM_APP_H
#define  PICAM_APP_H

/*===========================[  Inclusions  ]=============================================*/

#include <stddef.h>
#include <stdio.h>

/*============================[  Defines  ]==============================================*/


/*============================[  Global Variables  ]=====================================*/
/** \addtogroup global_constants	  
 *  @{
 */

/** Usage of arguments passed to application for option */
const char short_options [] = "d:ho:q:W:H:I:vc";

/** @} */

/*===========================[  Function declarations  ]=================================*/

/** \addtogroup internal_functions Internal Functions Internal Functions	  
 *  @{
 */

/**
 * @brief Helper function to parse and assign parameters from CLI.
 * 
 * @param[inout] argc   Input argument count
 * @param[inout] argv   Input argument vector
 * 
 */
void ParseArguments(int argc, char **argv);

/**
 * @brief   Helper function to print usage information 
 * 
 * @param[in] fp    File pointer
 * @param[in] argc  Input argument count
 * @param[in] argv  Input argument vector
 * 
 */
void usage(FILE* fp, int argc, char** argv);

/**
 * @brief   Checks if the filename has been provided for the CLI when running the PiCam library. 
 * 
 * @param[in] fname 
 * @param[in] argc  Input argument count
 * @param[in] argv  Input argument vector 
 * 
 */
void CheckValidationFilename (char* fname, int argc, char** argv);

/** @} */

#endif

/*==============================[  End of File  ]========================================*/
