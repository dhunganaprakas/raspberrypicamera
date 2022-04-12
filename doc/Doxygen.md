
Note: README file in the root directory describes all the necessary steps that are required to get Raspberry Pi Camera Library application up 
and running.

# Introduction 

This project is created to have basic camera functionalities of computer vision library using raspberry pi camera. During initial development 
of this project, the implementation was done using virtual Ubuntu machine using integrated camera. The application running on the raspberry pi 
might have problems regarding execution speed for computational heavy choices and maybe slower in response. 


# Purpose


# Description

# File Structure

|   Filename        |   Description             |
|:-----------------:|:-------------------------:|
| write.h           |   Header for declarations of write functions.
| write.c           |   Source file for implementation of saving image as jpeg and bmp  |
| PiCam_App.h       |   Header file for main application |
| PiCam_App.c       |   Implementation of main application |
| Common_PiCam.h    |   Header for common utility functions |
| Common_PiCam.c    |   Implementation of common utility functions |
| PiCam.h           |   Header for camera initialization, processing v4l2 buffers and de-initialization   |
| PiCam.c           |   Source file for implementation of APIs for initialization, processing v4l2 buffers and de-initialization |
| Convolutions.h    |   Header for convolution methods |
| Convolutions.c    |   Source for implementation of convolution methods |
| ColorConversion.h |   Header for color-space conversion functions |
| ColorConversion.c |   Implementation for color-space conversion functions |
| Edit.h            |   Header for editing functionalities |
| Edit.c            |   Implementation of editing functions |


@startuml

left to right direction
skinparam backgroundColor white
skinparam DefaultFontSize 14
skinparam DefaultFontName Times

folder Sources {
    together {
        folder App{
            file PiCam_App.c       #LightBlue
            file PiCam_App.h       #LightYellow
        }
        folder Common_PiCam{
            file Common_PiCam.c    #LightBlue
            file Common_PiCam.h    #LightYellow
        }
        folder PiCam{
            file PiCam.c           #LightBlue
            file PiCam.h           #LightYellow 
        }
        folder PiCamConvolutions{
            file Convolutions.c    #LightBlue
            file Convolutions.h    #LightYellow
        }
        folder PiCamUtils_ColorConv{
            file ColorConversion.c #LightBlue
            file ColorConversion.h #LightYellow
        }
        folder PiCamUtils_Edit{
            file Edit.c            #LightBlue
            file Edit.h            #LightYellow
        }
        folder PiCamUtils_Save{
            file write.c           #LightBlue
            file write.h           #LightYellow
        }
    }
}

PiCam_App.c         --> PiCam_App.h
Common_PiCam.c      --> Common_PiCam.h
PiCam.c             --> PiCam.h
Convolutions.c      --> Convolutions.h
ColorConversion.c   --> ColorConversion.h
Edit.c              --> Edit.h
write.c             --> write.h

PiCam_App.c         --> PiCam.h
PiCam_App.c         --> write.h
PiCam_App.c         --> Convolutions.h
PiCam_App.c         --> Edit.h
PiCam_App.c         --> ColorConversion.h

@enduml


# PiCam Library

## Macros
    \ref picam_defines
    \ref function_macros

## Globals
    \ref global_constants   \n
    \ref global_variables

## Data types
    \ref data_types

## Functions
    \ref interface_functions
    \ref internal_functions

# Acronyms

|   Abbreviations   |   Description     |
|:-----------------:|:-----------------:|
|   YUV  |  Color space for Luminance(Y) and Chrominance(UV)  |
|   v4l  |  Video for Linux |
|   API  |  Application Programming Interface   |
|   jpeg |  Joint Photographic Experts Group    |
|   bmp  |  Bitmap  |


# References


