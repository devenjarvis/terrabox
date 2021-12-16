# TerraBox (WIP)
A completely open source augemented reality sandbox built with an Intel Realsense D415 camera, a Raspberry Pi 4, the Godot game engine, and a custom built apparatus (plans also to be open sourced).

Right now I'm working on getting the docs in order. Give the repo a star and check back shortly for better information on what the project is and how to build, run, and/or contribute to it.

## Setup Raspberry Pi
This project assumes, and has only been tested with, a 4GB Raspberry Pi 4. Any other version of pi is untested and comes with no guarantees or support expectations. Furthermore, this project expects your Raspberry Pi 4 to be running a 64bit version of Ubuntu. Please reference the following instructions for proper setup:

TBD

## Install Realsense lib
Once Ubuntu is setup on your Raspberry Pi and you are able to access it, we need to install the Realsense lib on your Pi. To do so follow these instructions:

This is a really rough export of my install history, will be cleaned up:

sudo apt install gcc g++
    3  ./bootstrap-vcpkg.sh
    4  sudo apt install build-essential
    5  g++ --version
    6  ./bootstrap-vcpkg.sh
    7  sudo apt install ninja-build
    8  ./bootstrap-vcpkg.sh
    9  ./vcpkg integrate install
   10  export VCPKG_FORCE_SYSTEM_BINARIES=1
   11  ./vcpkg integrate install
   12  ./vcpkg install realsense2
   13  cmake --version
   14  sudo apt remove cmake
   15  sudo apt-get install apt-transport-https ca-certificates gnupg software-properties-common wget
   16  wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | sudo apt-key add -
   17  sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
   18  sudo apt-get update
   19  sudo apt-get install cmake
   20  cmake --version
   21  ./vcpkg install realsense2
   22  ./vcpkg update
   23  sudo apt-get install pkg-config
   24  ./vcpkg update
   25  ./vcpkg install realsense2
   26  sudo apt install autoreconf libudev-dev
   27  sudo apt install autoconf
   28  sudo apt install libudev-dev
   29  ./vcpkg install realsense2
   30  apt-get install autoreconf
   31  sudo apt-get install autoreconf
   32  sudo apt-get install dh-autoreconf
./vcpkg install realsense2

## Install Godot
Now that the realsense lib has been successfully installed on your system we want to install the Godot game engine so we can run, test, and build Terrabox. You can setup Godot with the following instructions:

Clone and build Gogot 3.4
`git clone -b 3.4 https://github.com/godotengine/godot.git'
`cd ./godot`
`scons platform=x11 target=release_debug tools=yes use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" -j4`

Build export templates
`scons platform=x11 tools=no target=release use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" bits=64 -j4`
`scons platform=x11 tools=no target=release_debug use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" bits=64 -j4`
`cd ./bin`
`mkdir /home/ubuntu/.local/share/godot/templates/3.4.1.rc`
`mv godot.x11.opt.64.llvm ~/.local/share/godot/templates/3.4.1.rc/linux_x11_64_release`
`mv godot.x11.opt.debug.64.llvm ~/.local/share/godot/templates/3.4.1.rc/linux_x11_64_debug`

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
