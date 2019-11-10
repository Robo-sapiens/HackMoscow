//
// Created by kira on 09.11.2019.
//

#include "arduino_serial.h"
#include "serial_talker.h"

//#define DEVICE "/dev/ttyACM0"  // could change but would rather not to
#define DEVICE "/dev/ttyUSB0"  // could change but would rather not to
#define DELAY 80000


void msg_sender(msg_buf &Msg_buf) {
    int filed = serialport_init(DEVICE, 9600);
    while (serialport_write(filed, Msg_buf.msg.data()) != -1) {
        usleep(DELAY);
    }
    serialport_flush(filed);
    serialport_close(filed);
}
