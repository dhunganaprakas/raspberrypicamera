# Raspberry Pi Camera Stream

Version History
---------------

05 March 2022:
+   Initial Template Created for capturing image from CLI and basic information regarding the PiCam 
    functionalities.

<div class="bottom"/>

Copyright and License
---------------------

Copyright (c) 2021-2022 Prakash Dhungana   
All rights reserved.


## Introduction 

This project is created to have basic camera functionalities of computer vision library using raspberry pi camera. During initial development of this project,
 the implementation was don using virtual Ubuntu machine using integrated camera. The application running on the raspberry pi might have problems regarding execution speed for computational heavy choices. 


## Purpose

    N/A

## Description

    N/A

## File Structure

The folder structure of this PiCam library is as follow.

|   Filename    |   Description             |
|:-------------:|:-------------------------:|
|   yuv.h       |   Header for YUV conversions  |
|   yuv.c       |   Source file for YUV color space formats conversion |
|   PiCam.h     |   Header for camera initialization, processing v4l2 buffers and de-initialization   |
|   PiCam.c     |   Source file for implementation of APIs for initialization, processing v4l2 buffers and de-initialization |


@startuml
rectangle {
    file yuv.c      #orange
    file yuv.h      #yellow
    file PiCam.c    #orange
    file PiCam.h    #yellow

    yuv.c --> yuv.h
    yuv.c --> unistd.h
    PiCam.h --> stdlib.h
    PiCam.h --> string.h
    PiCam.h --> jpeglib.h
    PiCam.h --> libv4l2.h
    PiCam.h --> signal.h
    PiCam.h --> inttypes.h
    PiCam.c --> yuv.h
    PiCam.c --> PiCam.h
    PiCam.c --> assert.h
    PiCam.c --> getopt.h
    PiCam.c --> fcntl.h
    PiCam.c --> errno.h
    PiCam.c --> stat.h
    PiCam.c --> ioctl.h
    PiCam.c --> videodev2.h
    PiCam.c --> mman.h

    skinparam legendbackgroundcolor #white
    legend left
    <back:orange>   </back> Source files for PiCam application 
    <back:yellow>   </back> Header files for PiCam application
    <back:lightgrey>   </back> External Header files
    endlegend

}
@enduml

## PiCam Library

    N/A


## Acronyms

|   Abbreviations   |   Description     |
|:-----------------:|:-----------------:|
|   YUV  | Colorspace for Luminance(Y) and Chrominance(UV)  |


## References

    N/A

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact