/**
 * @file PiCam_App.c
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief <b> Implementation of main application </b>
 * @version 0.1
 * @date 2022-04-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/

#include <getopt.h>
#include <signal.h>
#include <math.h>
#include "PiCam.h"
#include "PiCam_App.h"
#include "ColorConversion.h"
#include "write.h"
#include "Convolutions.h"
#include "Edit.h"

/*============================[  Global Variables  ]====================================*/

/** \addtogroup global_variables	Global Variables 
 *  @{
 */

/** Global buffer to save image */
struct buffer Image_Save;

/** Global buffer to store grayscale image */
struct buffer Image_grayscale;

/** @}*/

/** \addtogroup global_constants	Global Constants 
 *  @{
 */

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

/** @}*/

/*===========================[  Function definitions  ]=================================*/

/** \addtogroup internal_functions Internal Functions	  
 *  @{
 */

void usage(FILE* fp, int argc, char** argv)
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
				printf("Version V0.1.0 \nDate: 2022-04-12\n");
				exit(EXIT_SUCCESS);
				break;

			default:
				/* Prints usage formats from CLI */
				usage(stderr, argc, argv);
				exit(EXIT_FAILURE);
		}			
	}
}


void CheckValidationFilename (char* fname, int argc, char** argv)
{
	/** Checks for required parameters and prints help if not in order */
	if (!fname) 
	{
		fprintf(stderr, "You have to specify JPEG output filename!\n\n");
		usage(stdout, argc, argv);
		exit(EXIT_FAILURE);
	}
}

/** @} */

/*=======================[  Main Application  ]===============================*/

/** \addtogroup mainapp	Main Application 
 *  @{
 */

/**
 * @brief Main app for PiCam library.
 * 
 * @param[inout] argc	Input argument count
 * @param[inout] argv 	Input argument vector
 * 
 * @return int Return Status 
 * @retval EXIT_SUCCESS	Returned successfully
 * @retval EXIT_FAILURE	Error encountered
 *  
 */
   
int main(int argc, char **argv)
{
	ParseArguments(argc, argv);
	CheckValidationFilename (filename, argc, argv);
	CheckContinuousFlag(continuous);
	pixel_format = V4L2_PIX_FMT_YUV420;
	
	OpenCamera();
	InitCamera();
	StartCapture();
	CaptureFrame();
	StopCapture();
	DeInitCamera();
	CloseCamera();
	
	Image_Save.start = malloc(width*height*3);
	Image_grayscale.start = malloc(width*height);
	memcpy(Image_grayscale.start, Image_Buffer.start, width*height);	
	Convert_YUV420toYUV444(width, height, Image_Buffer.start, Image_Save.start);
	writejpegimageYUV(width, height, Image_Save.start, filename);

	exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}

/** @} */

/*==============================[  End of File  ]======================================*/
