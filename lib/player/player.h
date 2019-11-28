#ifndef __PLAYERH__
#define __PLAYERH__

#include <thread>
#include <string>
#include <cstdint>
#include <cmath>
#include <deque>
#include "LED.h"
#include "polygon.h"


class Player {
public:
    explicit Player(size_t delay, const char *device);
    ~Player();
    void render();

    size_t delay;
    std::string device;
    RGB rgb;
    std::deque<Polygon *> polygons;
    int32_t verteces;
    Point *base_polygon;
    Point *tr_matrix;
    int8_t mode;
    LED led_;

private:
    // singleton
    Player &operator=(Player const &);
    Player(Player const &);
};

void serial_interface(Player &player);
void show_leds(Player &player);

#endif