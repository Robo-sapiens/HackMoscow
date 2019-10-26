
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
    while (true) {
        std::cin >> msg;
        std::string msg_s = "<ффф>";
        int write_check = serialport_write(fd, msg_s.data());
        if (write_check == -1) {
            break;
        }
        std::cout << msg << std::endl;
        usleep(20000);
    }

    serialport_flush(fd);
    serialport_close(fd);
    return 0;
}
