# Raspberry Pi Camera Stream #

This README file provides necessary steps to step up the Raspberry Pi Camera Library.

## Introduction ##

This project is created to have basic camera functionalities of computer vision library using Raspberry Pi camera. During initial development of 
this project, the implementation was done using virtual Ubuntu machine using integrated camera. The application running on the raspberry pi might 
have problems regarding execution speed for computational heavy choices. If such problems are encountered, it is suggested to upgrade to the higher
RAM variant of available Raspberry Pi.

## Project Structure ##

The folder structure of Raspberry Pi Camera Library is as follow.

```bash
├── doc
│   ├── doxygen.ini
│   └── Doxygen.md
├── Makefile
├── README.md
└── Sources
    ├── App
    │   ├── PiCam_App.c
    │   └── PiCam_App.h
    ├── Common_PiCam
    │   ├── Common_PiCam.c
    │   └── Common_PiCam.h
    ├── PiCam
    │   ├── PiCam.c
    │   └── PiCam.h
    ├── PiCamConvolutions
    │   ├── Convolutions.c
    │   └── Convolutions.h
    ├── PiCamUtils_ColorConv
    │   ├── ColorConversion.c
    │   └── ColorConversion.h
    ├── PiCamUtils_Edit
    │   ├── Edit.c
    │   └── Edit.h
    └── PiCamUtils_Save
        ├── write.c
        └── write.h
```

### Quick summary ###

Captures the image and saves the output image in <Repository_root>/Build/<filename>.
- Version

V0.1.0  [First Release for Raspberry Pi]


### How do I set up done? ###

#### Dependencies

This library is dependent on v4l2 and jpeg library.  To set up the pre-conditions, please install these two libraries using following commands:

```
sudo apt-get install -y libv4l-dev
sudo apt-get install -y libjpeg-dev
```
For generating documentation of the project, the following packages needs to be installed. Please install these libraries using following commands:

```
sudo apt-get install -y doxygen
sudo apt-get install -y doxygen-gui
sudo apt-get install -y plantuml
sudo apt-get install -y graphviz default-jre
```

Finally, for building the Raspberry Pi Camera library, GNU make tool is used. Before progressing with the build, please install the GNU make tool 
using following command.
```
sudo apt-get install build-essential
sudo apt-get install make
``` 

#### Summary of set up

The library uses these libraries and information regarding individual packages can be found in the provided links.

    - Video for Linux Library [https://www.kernel.org/doc/html/v4.17/media/uapi/v4l/v4l2.html]
    - JPEG Library [https://libjpeg-turbo.org/]
    - Doxygen [https://www.doxygen.nl/index.html]
    - Plantuml [https://plantuml.com/]
    - Graphviz [https://graphviz.org/]
    - GNU [https://www.gnu.org/software/make/]

#### Configuration

Configuration required for build is setup in Makefile. If in-depth information and changes in configuration is required, the information on how to 
enable the changes is available in GNU make documentation. 

### How to run tests

For testing the application, you can perform following few steps.
- ./PiCam -v   or ./PiCam --version from <Repository_root>/Build/

Version information will be printed in the console. An example of the the console output is shown below:

```
Version V0.1.0 
Date: 2022-04-12
``` 

- ./PiCam -h   or ./PiCam --help from <Repository_root>/Build/

Information on how to run the application and all the available options are printed in the console. 

```
Usage: ./PiCam_App [options]

Options:
-d | --device name   Video device name [/dev/video0]
-h | --help          Print this message
-o | --output        Set JPEG output filename
-q | --quality       Set JPEG quality (0-100)
-W | --width         Set image width
-H | --height        Set image height
-I | --interval      Set frame interval (fps) (-1 to skip)
-c | --continuous    Do continuos capture, stop with SIGINT.
-v | --version       Print version
```

- ./Picam -o capture from <Repository_root>/Build/

Before running this command, please connect the camera device and enable the camera interface from Raspberry Pi preferences. If it is Ubuntu, check if the camera device is available from list of connected devices. This step is the actual step which captures the image and saves the output to  <Repository_root>/Build/capture.jpg. Open the image and check if 
capture was successful or not.

- Generating documentation 

For generating the documentation for Raspberry Pi Camera Library, locate the shell directory at  <Repository_root>/doc and run the following 
doxygen command.
```
doxygen doxygen.ini
```
A new folder named PiCam will be created in <Repository_root>/doc. To browse through the documents, open <Repository_root>/doc/PiCam/index.html 
file.
      

#### Deployment instructions

For specific use-case, please look the markdown file located in doc/Usecases.md

### Contribution guidelines ###

* Writing tests

Test cases can be added to test the functionalities of the application.

* Code review

Please reach out if there is any inconsistencies in the code or having trouble in setup of the project.

* Other guidelines

If you want to add additional functionality on top of the existing 

### Who do I talk to? ###

* Prakash Dhungana [dhunganaprakas@gmail.com]

## Version History ##

- [09th March 2022] Initial Template, capture and save as jpg image.
- [21st March 2022] Save bitmap(.bmp) image file.
- [24th March 2022] Implement convolution method for Gaussian, Sobel and Canny. 
- [27th March 2022] Implement Mean and Median filtering methods.
- [30th March 2022] Implement rotation functionality.
- [02nd April 2022] Implement scaling operations.
- [05th April 2022] Implement editing brightness and contrast functions.
- [12th April 2022] Updates for documentation fields.


## Copyright and License

Copyright (c) 2022 Prakash Dhungana   
