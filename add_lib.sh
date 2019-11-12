#!/bin/bash
sudo apt-get install libtool
sudo apt-get install autoconf
sudo apt-get install autopoint
sudo apt-get update
sudo apt-get install libcap-dev
sudo apt-get install libsndfile-dev
git clone https://gitlab.freedesktop.org/pulseaudio/pulseaudio.git 
cd pulseaudio
./bootstrap.sh
make
sudo make install
sudo ldconfig
pulseaudio --start -D


