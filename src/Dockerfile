FROM ubuntu:20.04 

# Init Ubuntu
RUN apt-get update
RUN apt-get install -y gnupg2
RUN apt-get install -y lsb-release
RUN apt-get install -y software-properties-common

# Setup Realsense

## Register the server's public key
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE || apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE

## Add the server to the list of repositories
RUN add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo $(lsb_release -cs) main" -u

## Install the libraries
RUN apt-get install -y librealsense2-dkms
RUN apt-get install -y librealsense2-utils

CMD ["realsense-viewer"]