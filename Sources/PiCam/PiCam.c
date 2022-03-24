/**
 * @file PiCam.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief   <b> Source for main application </b> 
 * @version 
 * @date 2022-03-03 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2022-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-03-24 Update for convolution methods
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/

#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <stdlib.h>
#include "PiCam.h"
#include "yuv.h"
#include "write.h"
#include "Convolutions.h"

/*============================[  Defines  ]=============================================*/

/** Define macro for clearing memory */
#define CLEAR(x) memset (&(x), 0, sizeof (x))

/*============================[  Global Variables  ]====================================*/

/** Global buffer to store the image to implement desired algorithms and to save it */
struct buffer Image_Buffer;

/** Global buffer to save image */
struct buffer Image_Save;

/** Global buffer to store grayscale image */
struct buffer Image_grayscale;


/*===========================[  Function definitions  ]=================================*/

/** Stops continuous capture
 */ 
void StopContCapture(int sig_id) 
{
	printf("Stoping continuous capture\n");
	continuous = 0;
}

/** Assigns signal interrupt handler function pointer
 */
void InstallSIGINTHandler() 
{
	struct sigaction sa;
	CLEAR(sa);
	
	sa.sa_handler = StopContCapture;
	if(sigaction(SIGINT, &sa, 0) != 0)
	{
		fprintf(stderr,"Could not install SIGINT handler, continuous capture disabled \n");
		continuous = 0;
	}
}

/** Input output control device driver
 */ 
static int xioctl(int fd, int req, void* argp)
{
	int r;

	do r = v4l2_ioctl(fd, req, argp);
	while (-1 == r && EINTR == errno);

	return r;
}

/** Updates the global buffer from captured buffer from v4l2 
 */ 
static void Update_LatestBuffer(const void* p, struct timeval timestamp)
{
	int image_size = width*height*3*sizeof(char)/2;
	unsigned char* src = (unsigned char*)p;
	Image_Buffer.start = malloc(image_size);
	memcpy(Image_Buffer.start, src, image_size);
}

/**	Read single frame from v4l2 buffer
*/
static int ReadBuffer(void)
{
	struct v4l2_buffer buf;
    CLEAR(buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) 
	{
        switch (errno) 
		{
            case EAGAIN:
                return 0;

            case EIO:
                // Could ignore EIO, see spec
                // fall through

            default:
                errno_exit("VIDIOC_DQBUF");
        }
    }

    assert(buf.index < n_buffers);
	Update_LatestBuffer(buffers[buf.index].start,buf.timestamp);

    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        errno_exit("VIDIOC_QBUF");

	return 0;
}

/**	Captures image buffer and stores them in 
*/
static void CaptureFrame(void)
{	
	int count;
	unsigned int numberOfTimeouts;

	numberOfTimeouts = 0;
	count = 3;
	printf("Updating image buffer \nSMILE PLEASE \n\t(-_-)\n");

	while (count-- > 0) {
		for (;;) {
			fd_set fds;
			struct timeval tv;
			int r;

			FD_ZERO(&fds);
			FD_SET(fd, &fds);

			/* Timeout. */
			tv.tv_sec = 1;
			tv.tv_usec = 0;

			r = select(fd + 1, &fds, NULL, NULL, &tv);

			if (-1 == r) {
				if (EINTR == errno)
					continue;

				errno_exit("select");
			}

			if (0 == r) {
				if (numberOfTimeouts <= 0) {
					count++;
				} else {
					fprintf(stderr, "select timeout\n");
					exit(EXIT_FAILURE);
				}
			}
			if(continuous == 1) {
				count = 3;
			}

			if (0 == ReadBuffer())
				break;

			/* EAGAIN - continue select loop. */
		}
	}
}

/**	Stop capturing v4l2 buffers
*/
static void StopCapture(void)
{
	enum v4l2_buf_type type;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
    errno_exit("VIDIOC_STREAMOFF");
}

/** Start capturing v4l2 buffers
*/
static void StartCapture(void)
{
	unsigned int i;
	enum v4l2_buf_type type;

    for (i = 0; i < n_buffers; ++i) 
    {
        struct v4l2_buffer buf;
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            errno_exit("VIDIOC_QBUF");
        }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
        errno_exit("VIDIOC_STREAMON");

}

/** De-initializes camera using v4l2_munmap 
*/
static void DeInitCamera(void)
{
	unsigned int i;

    for (i = 0; i < n_buffers; ++i)
        if (-1 == v4l2_munmap(buffers[i].start, buffers[i].length))
            errno_exit("munmap");

	free(buffers);
}

/** Initializes MMAP to capture image buffers form v4l2 library
 */ 
static void InitMMAP(void)
{
	struct v4l2_requestbuffers req;

	CLEAR(req);

	req.count = VIDIOC_REQBUFS_COUNT;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
		if (EINVAL == errno) {
			fprintf(stderr, "%s does not support memory mapping\n", deviceName);
			exit(EXIT_FAILURE);
		} else {
			errno_exit("VIDIOC_REQBUFS");
		}
	}

	if (req.count < 3) {
		fprintf(stderr, "Insufficient buffer memory on %s\n", deviceName);
		exit(EXIT_FAILURE);
	}

	buffers = calloc(req.count, sizeof(*buffers));

	if (!buffers) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
		struct v4l2_buffer buf;

		CLEAR(buf);

		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;

		if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
			errno_exit("VIDIOC_QUERYBUF");

		buffers[n_buffers].length = buf.length;
		buffers[n_buffers].start = v4l2_mmap(NULL,  /* Start anywhere */ 
                                            buf.length, PROT_READ | PROT_WRITE, /* Required */
                                            MAP_SHARED, /* Recommended */ 
                                            fd, 
                                            buf.m.offset);

		if (MAP_FAILED == buffers[n_buffers].start)
			errno_exit("mmap");
	}
}

/** Initialize v4l2 formats and check if the camera device supports the 
 * provided settings.
*/
void InitializeCameraFormats(struct v4l2_format format)
{
	struct v4l2_streamparm frameint;
	unsigned int min;

	// v4l2_format
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.width = width;
	format.fmt.pix.height = height;
	format.fmt.pix.field = V4L2_FIELD_INTERLACED;
	format.fmt.pix.pixelformat = pixel_format;

	if (-1 == xioctl(fd, VIDIOC_S_FMT, &format))
		errno_exit("VIDIOC_S_FMT");

	if (format.fmt.pix.pixelformat != pixel_format) {
		fprintf(stderr,"Libv4l didn't accept %d format. Can't proceed.\n",pixel_format);
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(stdout,"Capture successful in %d format \n", pixel_format);
	}

	/* Note VIDIOC_S_FMT may change width and height. */
	if (width != format.fmt.pix.width) {
		width = format.fmt.pix.width;
		fprintf(stderr,"Image width set to %i by device %s.\n", width, deviceName);
	}

	if (height != format.fmt.pix.height) {
		height = format.fmt.pix.height;
		fprintf(stderr,"Image height set to %i by device %s.\n", height, deviceName);
	}
	
  /* If the user has set the fps to -1, don't try to set the frame interval */
  if (fps != -1)
  {
    CLEAR(frameint);
    
    /* Attempt to set the frame interval. */
    frameint.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    frameint.parm.capture.timeperframe.numerator = 1;
    frameint.parm.capture.timeperframe.denominator = fps;
    if (-1 == xioctl(fd, VIDIOC_S_PARM, &frameint))
      fprintf(stderr,"Unable to set frame interval.\n");
  }

	/* Buggy driver paranoia. */
	min = format.fmt.pix.width * 2;
	if (format.fmt.pix.bytesperline < min)
		format.fmt.pix.bytesperline = min;
	min = format.fmt.pix.bytesperline * format.fmt.pix.height;
	if (format.fmt.pix.sizeimage < min)
		format.fmt.pix.sizeimage = min;

}

/** Initializes camera and camera formats to capture v4l2 buffers 
*/
static void InitCamera(void)
{
	struct v4l2_capability cap;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;

	if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) 
    {
		if (EINVAL == errno) 
        {
			fprintf(stderr, "%s is no V4L2 device\n",deviceName);
			exit(EXIT_FAILURE);
		} 
        else 
        {
			errno_exit("VIDIOC_QUERYCAP");
		}
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) 
    {
		fprintf(stderr, "%s is no video capture device\n",deviceName);
		exit(EXIT_FAILURE);
	}


    if (!(cap.capabilities & V4L2_CAP_STREAMING)) 
    {
        fprintf(stderr, "%s does not support streaming i/o\n",deviceName);
        exit(EXIT_FAILURE);
    }

	/* Select video input, video standard and tune here. */
	CLEAR(cropcap);

	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) 
    {
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		crop.c = cropcap.defrect; /* reset to default */

		if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) 
        {
			switch (errno) 
            {
				case EINVAL:
					/* Cropping not supported. */
					break;
				default:
					/* Errors ignored. */
					break;
			}
		}
	} 
    else 
    {
		/* Errors ignored. */
	}

	CLEAR(fmt);

	InitializeCameraFormats(fmt);
	InitMMAP();

}

/**	Closes camera
*/
static void CloseCamera(void)
{
	if (-1 == v4l2_close(fd))
		errno_exit("close");

	fd = -1;
}

/**	Open camera device
*/
static void OpenCamera(void)
{
	struct stat st;

	// stat file
	if (-1 == stat(deviceName, &st)) {
		fprintf(stderr, "Cannot identify '%s': %d, %s\n", deviceName, errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	// check if its device
	if (!S_ISCHR(st.st_mode)) {
		fprintf(stderr, "%s is no device\n", deviceName);
		exit(EXIT_FAILURE);
	}

	// open device
	fd = v4l2_open(deviceName, O_RDWR /* required */ | O_NONBLOCK, 0);

	// check if opening was successfull
	if (-1 == fd) {
		fprintf(stderr, "Cannot open '%s': %d, %s\n", deviceName, errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void CheckValidationFilename (char* fname, int argc, char** argv)
{
	/** Checks for required parameters and prints help if not in order */
	if (!fname) 
	{
		fprintf(stderr, "You have to specify JPEG output filename!\n\n");
		usage(stdout, argc, argv);
		exit(EXIT_FAILURE);
	}
}

static void CheckContinuousFlag( int flag)
{
	/** Continuous capture flag set to TRUE */
	if(continuous == 1) 
	{
		int max_name_len = snprintf(NULL,0,continuousFilenameFmt,filename,UINT32_MAX,INT64_MAX);
		filenamePart = filename;
		filename = calloc(max_name_len+1,sizeof(char));
		strcpy(filename,filenamePart);
	}
}

static void usage(FILE* fp, int argc, char** argv)
{
	fprintf(fp,
		"Usage: %s [options]\n\n"
		"Options:\n"
		"-d | --device name   Video device name [/dev/video0]\n"
		"-h | --help          Print this message\n"
		"-o | --output        Set JPEG output filename\n"
		"-q | --quality       Set JPEG quality (0-100)\n"
		"-W | --width         Set image width\n"
		"-H | --height        Set image height\n"
		"-I | --interval      Set frame interval (fps) (-1 to skip)\n"
		"-c | --continuous    Do continuos capture, stop with SIGINT.\n"
		"-v | --version       Print version\n"
		"",
		argv[0]);
}

void ParseArguments(int argc, char **argv)
{
	for (;;) 
	{
		int index, c = 0;
		c = getopt_long(argc, argv, short_options, long_options, &index);
		if (-1 == c)
			break;

		switch (c) 
		{
			case 0: /* getopt_long() flag */
				break;

			case 'd':
				/* In case of multiple camera, sets capture device */
				deviceName = optarg;
				break;

			case 'h':
				/* Prints help on usage from CLI */
				usage(stdout, argc, argv);
				exit(EXIT_SUCCESS);

			case 'o':
				/* Set saved image filename */
				filename = optarg;
				break;

			case 'q':
				/* Sets saved image JPEG quality */
				jpegQuality = atoi(optarg);
				break;

			case 'W':
				/* Sets captured image width */
				width = atoi(optarg);
				break;

			case 'H':
				/* Sets captured image height */
				height = atoi(optarg);
				break;
				
			case 'I':
				/* Sets fps */
				fps = atoi(optarg);
				break;

			case 'c':
				/* Sets flag for continuous capture */
				continuous = 1;
				InstallSIGINTHandler();
				break;
				
			case 'v':
				/* Prints version information */
				printf("Version \n");
				exit(EXIT_SUCCESS);
				break;

			default:
				/* Prints usage formats from CLI */
				usage(stderr, argc, argv);
				exit(EXIT_FAILURE);
		}			
	}
}

/*=======================[  Main Application  ]===============================*/

/**
 * @brief Main app for PiCam library.
 * 
 * @param[inout] argc	Input argument count
 * @param[inout] argv 	Input argument vector
 * 
 * @return int 
 * @retval EXIT_SUCCESS	Returned successfully
 * @retval EXIT_FAILURE	Error encountered
 *  
 */
   
int main(int argc, char **argv)
{
	ParseArguments(argc, argv);
	CheckValidationFilename (filename, argc, argv);
	CheckContinuousFlag(continuous);
	
	OpenCamera();
	InitCamera();
	StartCapture();
	CaptureFrame();
	StopCapture();
	DeInitCamera();
	CloseCamera();
	
	Image_Save.start = malloc(width*height);
	Image_grayscale.start = malloc(width*height);
	memcpy(Image_grayscale.start, Image_Buffer.start, width*height);
	
	//Convert_YUV420toYUV444(width, height, Image_Buffer.start, Image_Save.start);
	writejpeggrayscale(width, height, Image_grayscale.start, filename);

	GaussianFilter(width,height,Image_grayscale.start,Image_Save.start);
	filename = "blurred_image";
	writejpeggrayscale(width, height, Image_Save.start, filename);

	/** Global buffer to store grayscale image */
	struct buffer Image_canny;
	Image_canny.start = malloc(width*height);
	filename = "canny_image";
	EdgeDetector edgeMethod = METHOD_CANNY;
	Edge_Detector(width, height, Image_Save.start, Image_canny.start, edgeMethod);
	writejpeggrayscale(width, height, Image_canny.start, filename);

	struct buffer Image_sobel;
	Image_sobel.start = malloc(width*height);
	filename = "sobel_image";
	edgeMethod = METHOD_SOBEL;
	Edge_Detector(width, height, Image_Save.start, Image_sobel.start, edgeMethod);
	writejpeggrayscale(width, height, Image_sobel.start, filename);

	exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}

/*==============================[  End of File  ]======================================*/
