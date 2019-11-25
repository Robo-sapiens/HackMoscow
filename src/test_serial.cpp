//
// Created by antonrampage on 13.11.2019.
//
/*#include <iostream>
#include "serial.h"
#include <cstdint>
#define SERIAL_PORT "/dev/ttyAMA0"

int main() {
    int32_t file = serialport_init(SERIAL_PORT, 115200);
    serialport_flush(file);
    serialport_write(file, "hello");
    int rcount = 0;
    char buffer[10];
        char b[1];
        int i = 0;
	sleep(10);
        while(rcount = read(file, b, 1) > 0) {
            buffer[i] = b[0];
            i++;
        }
        tcflush(file, TCIOFLUSH);
        buffer[i] = '\0';
        printf("Received: %s\n", buffer);
    serialport_flush(file);
    serialport_close(file);
    return 0;
} */
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// lib for reader
//#include <sys/time.h>
//#include <sys/types.h>


#define SERIAL_PORT "/dev/serial0"

int main() {

    struct termios serial;
    char *str = "Hello";
    char buffer[10];

    printf("Opening %s\n", SERIAL_PORT);

    int fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    printf("serial %d\n", fd);
    if (fd == -1) {
        perror(SERIAL_PORT);
        return -1;
    }

    if (tcgetattr(fd, &serial) < 0) {
        perror("Getting configuration");
        return -1;
    }

    // Set up Serial Configuration
    serial.c_iflag = 0;
    serial.c_oflag = 0;
    serial.c_lflag = 0;
    serial.c_cflag = 0;

    serial.c_cc[VMIN] = 0;
    serial.c_cc[VTIME] = 0;

    serial.c_cflag = B115200 | CS8 | CREAD;

    tcsetattr(fd, TCSANOW, &serial); // Apply configuration

    // for sender
    printf("Sending: %s\n", str);
    while (1) {
        int wcount = write(fd, str, strlen(str));
        if (wcount < 0) {
            perror("Write");
            return -1;
        } else {
            printf("Sent %d characters\n", wcount);
        }
        sleep(1);
    }


    // for reader
//    fd_set rfds;
//    struct timeval tv = {5, 0};
//    FD_ZERO(&rfds);
//    FD_SET(fd, &rfds);
//    while (select(fd + 1, &rfds, NULL, NULL, NULL) > 0) {
//        int rcount = 0;
//        char b[1];
//        int i = 0;
//        while(rcount = read(fd, b, 1) > 0) {
//            buffer[i] = b[0];
//            i++;
//        }
//        tcflush(fd, TCIOFLUSH);
//        buffer[i] = '\0';
//        printf("Received: %s\n", buffer);
//    }
//    printf("data didn't arrive within 5 sec\n");
//    close(fd);

}


