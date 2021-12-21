# TerraBox (WIP)
A completely open source augemented reality sandbox built with an Intel Realsense D415 camera, a Raspberry Pi 4, the Godot game engine, and a custom built apparatus (plans also to be open sourced).

Right now I'm working on getting the docs in order. Give the repo a star and check back shortly for better information on what the project is and how to build, run, and/or contribute to it.

## Setup Raspberry Pi
This project assumes, and has only been tested with, a 4GB Raspberry Pi 4. Any other version of pi is untested and comes with no guarantees or support expectations. Furthermore, this project expects your Raspberry Pi 4 to be running a 32bit version of Raspbian. Please reference the following instructions for proper setup:

https://www.raspberrypi.com/documentation/computers/getting-started.html

## Install Realsense lib
Once Ubuntu is setup on your Raspberry Pi and you are able to access it, we need to install the Realsense lib on your Pi. To do so follow these instructions:

```console
$ sudo apt install clang llvm
$ cd ~/librealsense
$ mkdir build
$ cd build
$ export CC=/usr/bin/clang
$ export CXX=/usr/bin/clang++
$ cmake .. -DBUILD_EXAMPLES=true -DCMAKE_BUILD_TYPE=Release -DFORCE_LIBUVC=true -DOTHER_LIBS="-latomic"
$ make -j4
$ sudo make install
```


## Install Godot
Now that the realsense lib has been successfully installed on your system we want to install the Godot game engine so we can run, test, and build Terrabox. You can setup Godot with the following instructions:

Clone and build latest stable 3.X Godot
```console
$ sudo apt-get install build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev
$ git clone https://github.com/godotengine/godot.git -b 3.x
$ cd ./godot
$ scons platform=x11 target=release_debug tools=yes use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" -j4
```

Build export templates
```console
$ scons platform=x11 tools=no target=release use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" bits=64 -j4
$ scons platform=x11 tools=no target=release_debug use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" bits=64 -j4
$ cd ./bin
$ mkdir /home/ubuntu/.local/share/godot/templates/3.4.1.rc
$ mv godot.x11.opt.64.llvm ~/.local/share/godot/templates/3.4.1.rc/linux_x11_64_release
$ mv godot.x11.opt.debug.64.llvm ~/.local/share/godot/templates/3.4.1.rc/linux_x11_64_debug
```
## Pull down and setup this project
```console
$ git clone https://github.com/devenjarvis/terrabox.git
$ cd terrabox
$ git submodule update --init
$ cd godot-cpp
$ git submodule update --init
$ scons platform=linux use_llvm=yes
$ cd ..
$ scons platform=linux
```

## Build/Install Realsense Lib
Make sure you've built/installed the realsense library on your system. This process can vary by OS/System, check the README for instructions: https://github.com/IntelRealSense/librealsense



## Versions
Godot Version: 3.2.3
D415 Firmware: 05.12.07.100
librealsense SDK version: 2.28.1
