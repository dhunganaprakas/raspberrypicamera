/**
 * @file PiCam.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Header for the main application </b>
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
#include <signal.h>
#include <inttypes.h>
#include <jpeglib.h>

/*============================[  Defines  ]=============================================*/

/** Minimum number of buffers to request in VIDIOC_REQBUFS call */
#define VIDIOC_REQBUFS_COUNT 3

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

/** File descriptor */
static int fd = -1;

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

/** Default camera name in linux */
static char* deviceName = "/dev/video0";

/** Default pixel format to capture */
uint32_t pixel_format = V4L2_PIX_FMT_YUV420;

/** Filename to save images incase of continuous capture  */
static const char* const continuousFilenameFmt = "%s_%010"PRIu32"_%"PRId64".jpg";

static const char short_options [] = "d:ho:q:W:H:I:vc";

/** Usage of arguments passed to application */
static const struct option long_options [] = 
{
	{ "device",     required_argument,      NULL,           'd' },
	{ "help",       no_argument,            NULL,           'h' },
	{ "output",     required_argument,      NULL,           'o' },
	{ "quality",    required_argument,      NULL,           'q' },
	{ "width",      required_argument,      NULL,           'W' },
	{ "height",     required_argument,      NULL,           'H' },
	{ "interval",   required_argument,      NULL,           'I' },
	{ "version",	no_argument,			NULL,			'v' },
	{ "continuous",	no_argument,			NULL,			'c' },
	{ 0, 0, 0, 0 }
};

/*===========================[  Function declarations  ]===================================*/

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
 * @return int 
 * @retval  EXIT_SUCCESS  Returned successfully.
 * @retval  EXIT_FAILURE  Returned with error.
 * 
 */
static int xioctl(int fd, int req, void* argp);

/**
 * @brief Read single frame from buffer.
 * 
 * @return int
 * @retval EXIT_SUCCESS Operation successful
 * @retval EXIT_FAILURE Operation unsuccessful 
 * 
 */
static int ReadBuffer(void);

/**
 * @brief Function to read and process frames.
 * 
 */
static void CaptureFrame(void);

/**
 * @brief Stop capturing frames from buffer.
 * 
 */
static void StopCapture(void);

/**
 * @brief Start capturing frames from buffer.
 * 
 */
static void StartCapture(void);

/**
 * @brief De-initialization of device. 
 * 
 */
static void DeInitCamera(void);

/**
 * @brief Initialization of MMAP driver.
 * 
 */
static void InitMMAP(void);

/**
 * @brief Initialize v4l2 formats and checks if the camera settings are supported.
 * 
 * @param[in] format    Camera format to initialize
 */
void InitializeCameraFormats(struct v4l2_format format);

/**
 * @brief Initialization for v4l2 buffer for camera device.
 * 
 */
static void InitCamera(void);

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
 */
static void usage(FILE* fp, int argc, char** argv);

/**
 * @brief Checks if the filename has been provided for the CLI when running the PiCam library.
 * 
 * @param[in] fname 
 */
static void CheckValidationFilename (char* fname, int argc, char** argv);

/**
 * @brief Checks if the continuous flag is set and updates the filename formatting 
 * to save the captured image using timestamp.
 * 
 * @param[in] flag  Flag to set continuous capture
 */
static void CheckContinuousFlag( int flag);


#endif /** PICAM_H **/

/*==============================[  End of File  ]======================================*/
