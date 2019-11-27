//
// Created by kira on 27.11.2019.
//

#ifndef PLAYER_LIB_PLAYER_POLYGON_H_
#define PLAYER_LIB_PLAYER_POLYGON_H_

#include "LED.h"
#include <stdint-gcc.h>
#include <cstdlib>
#include <cmath>


class Polygon {
public:
    Polygon(size_t  verteces, int32_t r, int32_t g, int32_t b);
    ~Polygon();

    void set_items(const Point *matrix, size_t size);
    void operator*=(const Point *tr_matrix);

    size_t verteces;
    Point *vectors;
    float_t max_item;
    RGB color;
    float_t radius;
};

#endif //PLAYER_LIB_PLAYER_POLYGON_H_
