#include "player.h"
#include "serial.h"
#include "uart.h"
#include "LED.h"
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
    Point a = {-10, -2};
    Point b = {13, 4};
    RGB led_rgb= {30, 0, 0};
    //while(true) {
        //led.show_led_on_pi(player.rgb);
	led.draw_line(a, b, led_rgb);
      //  usleep(player.delay);
    //}
}
