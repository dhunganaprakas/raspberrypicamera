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

/** Doxygen compliant formatting for comments */

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
    /** Use read() call for buffers  */
    IO_METHOD_READ,
    /** Use memory mapped buffers  */
    IO_METHOD_MMAP,
    /** Use application allocated buffers */
    IO_METHOD_USERPTR,
} io_method;

struct buffer {
    /** Pointer to starting pixel position */
    unsigned char *  start;
    /** Pixel buffer length */
    size_t  length;
    /** Timestamp of captured image buffer */
    struct timeval timestamp;
};

/** I/O method to use for the library */
static io_method io = IO_METHOD_MMAP;

/** */
static int              fd              = -1;

/** Variable to store the captured buffer */
struct buffer * buffers = NULL;

/** Number of buffers */
static unsigned int n_buffers = 0;

/** Global camera settings */
/** Default camera setting for image width  */
static unsigned int width = 640;

/** Default camera setting for image height  */
static unsigned int height = 480;

/** Default camera setting for frames per seconds */
static unsigned int fps = 30;

/** Flag to store information whether ti capture continuous frame or not */
static int continuous = 0;

/** Variable to store lower limit for Canny edge detection. Default is set to 75 */
static int lim_canny_lower = 75;

/** Variable to store upper limit for Canny edge detection. Default is set to 150 */
static int lim_canny_upper = 150;

/** Variable to store limit for Sobel edge detection. Default is set to 100 */
static int lim_sobel = 100;

/** Default camera name in linux */
static char* deviceName = "/dev/video0";

/** Filename to save images incase of continuous capture  */
static const char* const continuousFilenameFmt = "%s_%010"PRIu32"_%"PRId64".jpg";

/*===========================[  Function declarations  ]===================================*/

/**
 * @brief Stop SIGINT interput handler
 * 
 * @param[in] sig_id Signal ID 
 * 
 */
void StopContCapture(int sig_id);

/**
 * @brief SIGINT interput handler
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
 * @brief Function to read and process frames
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
 * @brief De-initialization of device 
 * 
 */
static void DeInitCamera(void);

/**
 * @brief Initialization of MMAP driver
 * 
 */
static void InitMMAP(void);

/**
 * @brief Initialize v4l2 formats and checks if the camera settings are supported
 * 
 */
void InitializeCameraFormats(struct v4l2_format format);

/**
 * @brief Initialization for v4l2 buffer for camera device 
 * 
 */
static void InitCamera(void);



#endif /** PICAM_H **/

/*==============================[  End of File  ]======================================*/
