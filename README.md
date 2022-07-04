# TerraBox  - A prototype
An open source augemented reality sandbox prototype, that projects terrain images over a kids' sandbox in real-time. Built with an Intel Realsense D415 camera, a Raspberry Pi 4, the Godot game engine, and a custom built apparatus. This is a custom prototype and may not work out-of-the-box for other users. 

# Gallery
![Portrait view of AR Sandbox, running](/media/ar_sandbox_portrait.png)

![Close-up view of AR Sandbox, running](/media/ar_sandbox_closeup.png)

# Running
A pre-built binary called `terrabox` can be found in the `/bin` directory. 

As noted, this has been specifically calibrated to work with the current prototype and likely will not work out of the box for others. Please see the "Building" section below to understand how to build the project on a Raspberry Pi and/or feel free to explore the code itself. It took me a lot of trial and error to get Godot and the Intel Realsense camera playing together nicely, so I hope this code helps anyone else trying to do the same.

# Building
## Setup Raspberry Pi
This project assumes, and has only been tested with, a 4GB Raspberry Pi 4. Any other version of pi is untested and comes with no guarantees or support expectations. Furthermore, this project expects your Raspberry Pi 4 to be running a 32bit version of Raspbian. Please reference the following instructions for proper setup:

https://www.raspberrypi.com/documentation/computers/getting-started.html

## Install Realsense lib
Once Raspbian is setup on your Raspberry Pi and you are able to access it, we need to install the Realsense lib on your Pi. To do so follow these instructions:

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
Now that the realsense lib has been successfully installed on your system we want to install the Godot game engine so we can run, test, and build Terrabox. 

I recommend downloading pre-built binaries/export templates for Godot 3.4.4 from [this repo](https://github.com/hiulit/Unofficial-Godot-Engine-Raspberry-Pi).

If you need a custom Godot setup you may use the following, optional instructions, but keep in mind it is a long build process.

#### Clone and build latest stable 3.X Godot
```console
$ sudo apt-get install build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev
$ git clone https://github.com/godotengine/godot.git -b 3.x
$ cd ./godot
$ scons platform=x11 target=release_debug tools=yes use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" -j4
```

#### Build export templates
```console
$ scons platform=x11 target=release tools=no use_llvm=yes CCFLAGS="-mcpu=cortex-a72 -mtune=cortex-a72 -mfpu=neon-fp-armv8 -mfloat-abi=hard -mlittle-endian -munaligned-access" -j4
$ scons platform=x11 tools=no target=release use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" bits=32 -j4
$ scons platform=x11 tools=no target=release_debug use_llvm=yes CCFLAGS="-mtune=cortex-a72 -mcpu=cortex-a72 -mfloat-abi=hard -mlittle-endian -munaligned-access -mfpu=neon-fp-armv8" bits=32 -j4
$ cd ./bin
$ mkdir /home/ubuntu/.local/share/godot/templates/3.4.2.rc
$ mv godot.x11.opt.32.llvm ~/.local/share/godot/templates/3.4.2.rc/linux_x11_32_release
$ mv godot.x11.opt.debug.32.llvm ~/.local/share/godot/templates/3.4.2.rc/linux_x11_32_debug
```
## Pull down and setup this project
```console
$ git clone https://github.com/devenjarvis/terrabox.git
$ cd terrabox
$ git submodule update --init
$ cd godot-cpp
$ git submodule update --init
$ scons platform=linux generate_bindings=yes use_llvm=yes -j4
$ cd ..
$ scons platform=linux use_llvm=yes -j4
```


# Versions
Godot Version: 3.4.4
D415 Firmware: 05.12.07.100
librealsense SDK version: 2.28.1
