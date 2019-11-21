#include <iostream>
#include "player.h"

#define DELAY 70000
#define SERIAL_PORT "/dev/ttyAMA0"


int main(int argc, char **argv) {
    Player player(DELAY, SERIAL_PORT);
    std::thread t1(serial_interface, std::ref(player));
    std::thread t2(show_leds, std::ref(player));
    t1.join();
    t2.join();
    return 0;
}
