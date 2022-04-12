/**
 * @file write.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief   <b> Header for writing image files </b>
 * @version 
 * @date 2022-03-06 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2033-03-23 Updates for Gaussian filter and Edge detection
 * @date 2022-04-05 Add saving images for JPEG RGB
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/


/*============================[  Data Types  ]============================================*/

/** \addtogroup data_types	  
 *  @{
 */

/** BMP file header structure */
typedef struct                       
{
    /** Size of file */
    unsigned int   bfSize;  
    /** Reserved - BMP standard */         
    unsigned short bfReserved1;
    /** Reserved - BMP standard */      
    unsigned short bfReserved2;
    /** Offset to bitmap pixel data */      
    unsigned int   bfOffBits;        
} BITMAPFILEHEADER;


/** BMP file info structure */
typedef struct                       
{
    /** Image size of file info header */
    unsigned int   biSize;           
    /** Width of image */
    int            biWidth;          
    /** Height of image */
    int            biHeight;         
    /** Number of color planes */
    unsigned short biPlanes;         
    /** Number of bits per pixel */
    unsigned short biBitCount;       
    /** Number of bits per pixel */
    unsigned int   biCompression;    
    /** Size of image data */
    unsigned int   biSizeImage;      
    /** X pixels per meter */
    int            biXPelsPerMeter;  
    /** Y pixels per meter */
    int            biYPelsPerMeter;  
    /** Number of colors used */
    unsigned int   biClrUsed;        
    /** Number of important colors */
    unsigned int   biClrImportant;   
} BITMAPINFOHEADER;

/** @} */

/*============================[  Global Variables  ]=======================================*/

/** \addtogroup global_variables	  
 *  @{
 */

/** Image quality for JPEG compression */
static unsigned char jpegQuality = 70;

/** Pointer to store image filename */
static char* filename = NULL;

/** Filename extension */
static char* filenamePart = NULL;

/** @} */

/*===========================[  Function declarations  ]===================================*/

/** \addtogroup interface_functions Interface Functions	  
 *  @{
 */

/**
 * @brief Print error message and terminate program with EXIT_FAILURE return code. 
 * 
 * @param[in] string_ptr    Error message to print
 *  
 */
void errno_exit(const char* string_ptr);

/**
 * @brief Write image as a bmp file format.
 * 
 * @param[in] width     Width of image to be saved
 * @param[in] height    Height of image to be saved 
 * @param[in] src       Input pointer containing image buffer
 * @param[in] filename  Filename for image to save
 */
void writebitmapimage(int width, int height, unsigned char* src, char* filename);

/**
 * @brief Write image as a JPEG file format.
 * 
 * @param[in] width     Width of image to be saved
 * @param[in] height    Height of image to be saved
 * @param[in] img       Input pointer containing image buffer
 * @param[in] filename  Filename for image to save
 * 
 */
void writejpegimageYUV(int width, int height, unsigned char* img, char* filename);

/**
 * @brief Write image as a JPEG file format.
 * 
 * @param[in] width     Width of image to be saved
 * @param[in] height    Height of image to be saved
 * @param[in] img       Input pointer containing image buffer
 * @param[in] filename  Filename for image to save
 * 
 */
void writejpegimageRGB(int width, int height, unsigned char* img, char* filename);

/**
 * @brief Write image as a JPEG file format.
 * 
 * @param[in] width     Width of image to be saved
 * @param[in] height    Height of image to be saved
 * @param[in] img       Input pointer containing image buffer
 * @param[in] filename  Filename for image to save
 * 
 */
void writejpeggrayscale(int width, int height, unsigned char* img, char* filename);

/** @} */

/*==============================[  End of File  ]======================================*/
