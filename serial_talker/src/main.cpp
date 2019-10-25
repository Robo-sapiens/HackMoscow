#include <arduino_serial.h>
#include <iostream>
#include <unistd.h>

#define MSG_SIZE 16


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int fd = serialport_init(argv[1], 9600);
    char msg[MSG_SIZE];
//    std::stringstream ss;
    while (true) {
        std::cin >> msg;
//        ss << ;
        //    sprintf(msg, "<%d>", );
        int write_check = serialport_write(fd, msg);
        if (write_check == -1) {
            break;
        }
        usleep(60000);
    }

    serialport_flush(fd);
    serialport_close(fd);
    return 0;
}
