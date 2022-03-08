/**
 * @file PiCam.h
 * @author Prakash Dhungana (dhunganaprakas)
 * @brief Header for the main application
 * @version 0.0.1
 * @date 2022-03-03 Initial template
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*===========================[  Compile Flags  ]==========================================*/

#ifndef PICAM_H
#define  PICAM_H

/*===========================[  Inclusions  ]=============================================*/

#include <stdlib.h>
#include <string.h>
#include <libv4l2.h>
#include <signal.h>
#include <inttypes.h>
#include <jpeglib.h>

/*============================[  Defines  ]=============================================*/

/** Minimum number of buffers to request in VIDIOC_REQBUFS call */
#define VIDIOC_REQBUFS_COUNT 2

/*============================[  Data Types  ]==========================================*/

/** Enumeration fot I/O method configuration */
typedef enum {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
} io_method;

struct buffer {
    unsigned char *  start;
    size_t  length;
    struct timeval timestamp;
};

static io_method        io              = IO_METHOD_MMAP;
static int              fd              = -1;
struct buffer *         buffers         = NULL;
static unsigned int     n_buffers       = 0;

/** Global camera settings */
/** Camera setting for image width  */
static unsigned int width = 640;

/** Camera setting for image height  */
static unsigned int height = 480;

/** Camera setting for frames per seconds */
static unsigned int fps = 30;

/** Global camera settings */
static int continuous = 0;
static int canny = 0;
static int sobel = 0;
static int guassianblur = 0;
static char* deviceName = "/dev/video0";

static const char* const continuousFilenameFmt = "%s_%010"PRIu32"_%"PRId64".jpg";

/*===========================[  Function declarations  ]===================================*/

/**
 * @brief Stop SIGINT interput handler
 * 
 * @param[in] sig_id Signal ID 
 */
void StopContCapture(int sig_id);

/**
 * @brief SIGINT interput handler
 * 
 */
void InstallSIGINTHandler(); 

/**
 * @brief Implementation of wrapper around v4l2_ioctl.
 * Do ioctl and retry if error EINTR was returned. A signal
 * was caught during the ioctl() operation. Parameters are
 * the same as on ioctl.
 * 
 * @param[in] fd    File descriptor
 * @param[in] req   Request
 * @param[in] argp  Argument 
 * 
 * @return int 
 * @retval
 * @retval
 * 
 */
static int xioctl(int fd, int req, void* argp);

/**
 * @brief Process v4l2 buffer  
 * 
 * @param p     Buffer to receive v4l2 buffer      
 * @param tstp  Timestamp of received buffer
 * 
 */
static void Saveas_Jpeg(const void* p, struct timeval tstp);

/**
 * @brief Read single frame from buffer
 * 
 * @return int 
 * 
 */
static int read_buffer(void);

/**
 * @brief Main loop to read and process frames
 * 
 */
static void CaptureFrame(void);

/**
 * @brief Stop capturing frames from buffer
 * 
 */
static void StopCapture(void);

/**
 * @brief Start capturing frames from buffer
 * 
 */
static void StartCapture(void);

/**
 * @brief Deinitialization of device 
 * 
 */
static void DeInitCamera(void);

/**
 * @brief Initialization of MMAP driver
 * 
 */
static void InitMMAP(void);

/**
 * @brief Initialization for v4l2 buffer from camera device 
 * 
 */
static void InitCamera(void);



#endif /** PICAM_H **/

/*==============================[  End of File  ]======================================*/
