/**
 * @file write.h
 * @author Prakash Dhungana (dhunganaprakas@gmail.com)
 * @brief   <b> Header for writing image files </b>
 * @version 
 * @date 2022-03-06 Initial template
 * @date 2022-03-21 Updates for saving BMP image
 * @date 2033-03-23 Updates for Gaussian filter and Edge detection
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Doxygen compliant formatting for comments */

/*===========================[  Inclusions  ]=============================================*/


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

/** Image quality for JPEG compression */
static unsigned char jpegQuality = 70;

/** Pointer to store image filename */
static char* filename = NULL;

/** Filename extension */
static char* filenamePart = NULL;


/**
 * @brief Print error message and terminate program with EXIT_FAILURE return code. 
 * 
 * @param string_ptr    Error message to print
 *  
 */
void errno_exit(const char* string_ptr);

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param src 
 * @param filename 
 */
void writebitmapimage(int width, int height, unsigned char* src, char* filename);

/**
 * @brief Write image as a JPEG file format.
 * 
 * @param width
 * @param height
 * @param img       Input pointer containing image buffer
 * @param filename  Filename for image to save
 * 
 */
void writejpegimage(int width, int height, unsigned char* img, char* filename);

/**
 * @brief Write image as a JPEG file format.
 * 
 * @param width
 * @param height
 * @param img       Input pointer containing image buffer
 * @param filename  Filename for image to save
 * 
 */
void writejpeggrayscale(int width, int height, unsigned char* img, char* filename);

/*==============================[  End of File  ]======================================*/
