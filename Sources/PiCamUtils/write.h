/**
 * @file write.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

typedef struct                       /**** BMP file header structure ****/
    {
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
    } BITMAPFILEHEADER;

typedef struct                       /**** BMP file info structure ****/
    {
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
    } BITMAPINFOHEADER;

static unsigned char jpegQuality = 70;
static char* filename = NULL;
static char* filenamePart = NULL;


/**
 * @brief Print error message and terminate programm with EXIT_FAILURE return code. 
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
 * @param img   Input pointer containing image buffer
 * @param filename Filename for image to save
 * 
 */
void writejpegimage(int width, int height, unsigned char* img, char* filename);

