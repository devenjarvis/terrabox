# TerraBox (WIP)
A completely open source augemented reality sandbox built with an Intel Realsense D415 camera, a Raspberry Pi 4, the Godot game engine, and a custom built apparatus (plans also to be open sourced).

Right now I'm working on getting the docs in order. Give the repo a star and check back shortly for better information on what the project is and how to build, run, and/or contribute to it.

## Setup Raspberry Pi
This project assumes, and has only been tested with, a 4GB Raspberry Pi 4. Any other version of pi is untested and comes with no guarantees or support expectations. Furthermore, this project expects your Raspberry Pi 4 to be running a 64bit version of Ubuntu. Please reference the following instructions for proper setup:

TBD

## Install Realsense lib
Once Ubuntu is setup on your Raspberry Pi and you are able to access it, we need to install the Realsense lib on your Pi. To do so follow these instructions:

TBD

## Install Godot
Now that the realsense lib has been successfully installed on your system we want to install the Godot game engine so we can run, test, and build Terrabox. You can setup Godot with the following instructions:

TBD

## Pull down and setup this project
`git clone https://github.com/devenjarvis/terrabox.git`  
`cd terrabox`  
`git submodule update --init`  
`cd godot-cpp`  
`git submodule update --init`  
`scons platform=linux use_llvm=yes bits=64`  
`cd ..`  
`scons platform=linux`  

## Build/Install Realsense Lib
Make sure you've built/installed the realsense library on your system. This process can vary by OS/System, check the README for instructions: https://github.com/IntelRealSense/librealsense



## Versions
Godot Version: 3.2.3
D415 Firmware: 05.12.07.100
librealsense SDK version: 2.28.1
