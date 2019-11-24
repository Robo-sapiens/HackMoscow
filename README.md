# HackMoscow
*dependencies for build:*

qt5:
>qt5 itself\
>sudo apt-get install libqt5serialport5\
>sudo apt-get install libqt5serialport5-dev

pulse audio dependencies:

>sudo apt-get install libtool\
>sudo apt-get install autoconf\
>sudo apt-get install autopoint\
>sudo apt-get update\
>sudo apt-get install libcap-dev\
>sudo apt-get install libsndfile-dev

pulse audio:

>git clone https://gitlab.freedesktop.org/pulseaudio/pulseaudio.git\
>cd pulseaudio\
>./bootstrap.sh\
>make\
>sudo make install\
>sudo ldconfig\
>pulseaudio --start -D


*dependencies for release:*

pulse audio dependencies:

>sudo apt-get install libtool\
>sudo apt-get install autoconf\
>sudo apt-get install autopoint\
>sudo apt-get update\
>sudo apt-get install libcap-dev\
>sudo apt-get install libsndfile-dev

pulse audio:

>git clone https://gitlab.freedesktop.org/pulseaudio/pulseaudio.git\
>cd pulseaudio\
>./bootstrap.sh\
>make\
>sudo make install\
>sudo ldconfig\
>pulseaudio --start -D
