#ifndef __PLAYERH__
#define __PLAYERH__

#include <thread>
#include <string>
#include <cstdint>
#include <cmath>
#include "LED.h"


class Player
{
public:
    explicit Player(size_t delay, const char * device);

    size_t delay;
    std::string device;
    RGB rgb;
    int8_t error_code;
private:
    // singleton
    Player &operator=(Player const &);
    Player (Player const &);
};

void serial_interface(Player &player);
void show_leds(Player &player);

#endif