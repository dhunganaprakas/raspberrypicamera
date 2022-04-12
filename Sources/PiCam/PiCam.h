/**
 * @file PiCam.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for camera initialization, processing v4l2 buffers and de-initialization </b>
 * @version 
 * @date 2022-03-03 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2022-03-23 Updates for Gaussian filter and Edge detection
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef PICAM_H
#define  PICAM_H

/*===========================[  Inclusions  ]=============================================*/

#include <stdlib.h>
#include <string.h>
#include <libv4l2.h>
#include <inttypes.h>
#include <linux/videodev2.h>
#include "Common_PiCam.h"

/*============================[  Defines  ]=============================================*/

/** \addtogroup picam_defines	  
 *  @{
 */

/** Minimum number of buffers to request in VIDIOC_REQBUFS call */
#define VIDIOC_REQBUFS_COUNT 3

/** @} */

/*============================[  Data Types  ]==========================================*/

/** \addtogroup data_types	  
 *  @{
 */

/** Enumeration fot I/O method configuration */
typedef enum {
    /** Use read() call for buffers  */
    IO_METHOD_READ,
    /** Use memory mapped buffers  */
    IO_METHOD_MMAP,
    /** Use application allocated buffers */
    IO_METHOD_USERPTR,
} io_method;

typedef struct
{
    /** Width of source image */
    int width;
    /** Hight of source image */
    int height;
    /** Pointer to starting pixel position */
    u_int16_t*  start;
} Image_HSV;

/** @} */

/*============================[  Global Variables  ]=====================================*/

/** \addtogroup global_variables	  
 *  @{
 */

/** I/O method to use for the library */
static io_method io = IO_METHOD_MMAP;

/** File descriptor */
static int fd = -1;

/** Variable to store the captured buffer */
struct buffer* img_buffer;

/** Number of buffers */
static unsigned int n_buffers = 0;

/** Global camera settings */
/** Default camera setting for image width  */
static unsigned int width = 640;

/** Default camera setting for image height  */
static unsigned int height = 480;

/** Default camera setting for frames per seconds */
static unsigned int fps = 30;

/** Default camera name in linux */
static char* deviceName = "/dev/video0";

/** Default pixel format to capture */
uint32_t pixel_format;

/** @} */

/** \addtogroup global_constants	  
 *  @{
 */

/** Filename to save images incase of continuous capture  */
static const char* const continuousFilenameFmt = "%s_%010"PRIu32"_%"PRId64".jpg";

/** @} */

/*===========================[  Function declarations  ]===================================*/

/** \addtogroup internal_functions Internal Functions	  
 *  @{
 */

/**
 * @brief Stop SIGINT interput handler.
 * 
 * @param[in] sig_id Signal ID 
 * 
 */
void StopContCapture(int sig_id);

/**
 * @brief SIGINT interput handler.
 * 
 */
void InstallSIGINTHandler(void); 

/**
 * @brief Implementation of wrapper around v4l2_ioctl. Capture ioctl buffer 
 * and retry if error EINTR was returned. A signal was caught during the 
 * ioctl() operation. Parameters are the same as on ioctl.
 * 
 * @param[in] fd    File descriptor
 * @param[in] req   Request
 * @param[in] argp  Argument 
 * 
 * @return int Input output control status
 * @retval  EXIT_SUCCESS  Returned successfully.
 * @retval  EXIT_FAILURE  Returned with error.
 * 
 */
int xioctl(int fd, int req, void* argp);

/**
 * @brief Read single frame from buffer.
 * 
 * @return int  Operation Status
 * @retval EXIT_SUCCESS Operation successful
 * @retval EXIT_FAILURE Operation unsuccessful 
 * 
 */
int ReadBuffer(void);

/**
 * @brief   Function to update local and global image pixel buffer from captured v4l2 buffer.   
 * 
 * @param[in] p         Pointer to captured buffer
 * @param[in] timestamp Timestamp of captured buffer 
 * 
 */
void Update_LatestBuffer(const void* p, struct timeval timestamp);

/**
 * @brief Initialization of MMAP driver.
 * 
 */
void InitMMAP(void);

/**
 * @brief Initialize v4l2 formats and checks if the camera settings are supported.
 * 
 * @param[in] format    Camera format to initialize
 */
void InitializeCameraFormats(struct v4l2_format format);

/**
 * @brief Checks if the continuous flag is set and updates the filename formatting 
 * to save the captured image using timestamp.
 * 
 * @param[in] flag  Flag to set continuous capture
 */
void CheckContinuousFlag( int flag);

/** @} */

/** \addtogroup interface_functions Interface Functions	  
 *  @{
 */

/**
 * @brief Function to read and process frames.
 * 
 */
void CaptureFrame(void);

/**
 * @brief Stop capturing frames from buffer.
 * 
 */
void StopCapture(void);

/**
 * @brief Start capturing frames from buffer.
 * 
 */
void StartCapture(void);

/**
 * @brief De-initialization of device. 
 * 
 */
void DeInitCamera(void);

/**
 * @brief Initialization for v4l2 buffer for camera device.
 * 
 */
void InitCamera(void);

/**
 * @brief Function to open camera device.
 * 
 */
void OpenCamera(void);

/**
 * @brief Function to close camera device.
 * 
 */
void CloseCamera(void);

/** @} */

#endif /** PICAM_H **/

/*==============================[  End of File  ]======================================*/
