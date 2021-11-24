# TerraBox (WIP)
A completely open source augemented reality sandbox built with an Intel Realsense D415 camera, a Raspberry Pi 4, the Godot game engine, and a custom built apparatus (plans also to be open sourced).

Right now I'm working on getting the docs in order. Give the repo a star and check back shortly for better information on what the project is and how to build, run, and/or contribute to it.

## Pull down and setup this project
`git clone https://github.com/devenjarvis/terrabox.git`
`cd terrabox`
`git submodule update --init`
`cd godot-cpp`
`git submodule update --init`
`scons platform=osx arch=arm64 generate_bindings=yes -j8`
`cd ..`

## Build/Install Realsense Lib
Make sure you've built/installed the realsense library on your system. This process can vary by OS/System, check the README for instructions: https://github.com/IntelRealSense/librealsense



## Versions
Godot Version: 3.2.3
D415 Firmware: 05.12.07.100
librealsense SDK version: 2.28.1
