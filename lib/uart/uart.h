#ifndef __LIB_UART__
#define __LIB_UART__

#include <iostream>
#include <cstdint>
#include "LED.h"

void read_serial_port(int32_t file, RGB &led_rgb);

#endif // __LIB_UART__
