//
// Created by kira on 23.11.2019.
//

#ifndef PLAYER_UI_POLYGON_H
#define PLAYER_UI_POLYGON_H

#include <stdint-gcc.h>
#include <cstdlib>
#include <QPoint>
#include <QtGui/QColor>
#include <cmath>
#include <vector>

struct fPoint {
    float x;
    float y;
};

class Polygon {
public:
    Polygon(size_t verteces, int32_t r, int32_t g, int32_t b, float_t radius = 0, int32_t mode = 0);
    Polygon(const Polygon &other);
    ~Polygon();

    void set_items(const fPoint *matrix);
    void operator*=(const fPoint *tr_matrix);
    void push_back(fPoint item);
    void pop_back();

    size_t verteces;
    std::vector<fPoint> *real_vectors;
    std::vector<QPoint> *vectors;
    float_t max_item;
    QColor  color;
    float_t radius;
    int32_t mode;
    float_t rotation;
    // mode == 0 - polygon
    // mode == 1 - circle
    // mode == 2 - basic
};

#endif //PLAYER_UI_POLYGON_H
