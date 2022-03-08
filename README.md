# Raspberry Pi Camera Stream

This README would normally document whatever steps are necessary to get your application up and running.

## Introduction 

This project is created to have basic camera functionalities of computer vision library using raspberry pi camera. During initial development of this project,
 the implementation was don using virtual Ubuntu machine using integrated camera. The application running on the raspberry pi might have problems regarding execution speed for computational heavy choices. 


## Purpose





## Description




## File Structure

The folder structure of this PiCam library is as follow.

|   Filename    |   Description             |
|:-------------:|:-------------------------:|
|   yuv.h       |   Header for YUV conversions  |
|   yuv.c       |   Source file for YUV color space formats conversion |
|   write.h     |   Header for declarations of write functions.
|   write.c     |   Source file for implementation of saving image as jpeg and bmp  |
|   PiCam.h     |   Header for camera initialization, processing v4l2 buffers and de-initialization   |
|   PiCam.c     |   Source file for implementation of APIs for initialization, processing v4l2 buffers and de-initialization |
|

## PiCam Library



## Acronyms

|   Abbreviations   |   Description     |
|:-----------------:|:-----------------:|
|   YUV  | Color space for Luminance(Y) and Chrominance(UV)  |
|   v4l  |  Video for Linux |




## References


### What is this repository for? ###

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

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

## Version History

*[05 March 2022] Initial Template Created for capturing image from CLI and basic information regarding the PiCam functionalities.


## Copyright and License

Copyright (c) 2021-2022 Prakash Dhungana   
All rights reserved.