#include "player.h"
#include "serial.h"
#include "uart.h"

#define BAUDRATE 19200


Player::Player(size_t delay, const char * device) :
    delay(delay), device(device), rgb({0, 0, 0}), error_code(0) {}


void serial_interface(Player &player) {
    int32_t filed = serialport_init(player.device.c_str(), BAUDRATE);
    serialport_flush(filed);
    read_serial_port(filed, '<', '>', player.rgb);
    serialport_flush(filed);
    serialport_close(filed);
}


void show_leds(Player &player) {
    LED led;
    while(true) {
        led.show_led_on_pi(player.rgb);
        usleep(player.delay);
    }
}