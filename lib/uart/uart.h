#ifndef __LIB_UART__
#define __LIB_UART__

#include <iostream>
#include <cstdint>
#include "LED.h"
#include "serial.h"

#define SERIAL_PORT "/dev/ttyAMA0"

void read_serial_port(int32_t file, char s, char f, RGB &led_rgb);

#endif // __LIB_UART__
