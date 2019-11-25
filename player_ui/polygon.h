//
// Created by kira on 23.11.2019.
//

#ifndef PLAYER_UI_POLYGON_H
#define PLAYER_UI_POLYGON_H

#include <stdint-gcc.h>
#include <cstdlib>
#include <QTime>
#include <QPoint>
#include <QtGui/QColor>
#include <cmath>

class Polygon {
public:
    Polygon(size_t verteces, int32_t r, int32_t g, int32_t b);
    Polygon(const Polygon &other);
    ~Polygon();

    void set_items(const float_t *matrix, size_t size);
    float_t *operator()(size_t row, size_t col);
    void operator*=(float_t coef);
    void operator*=(const float_t *tr_matrix);

    size_t  rows;
    size_t  cols;
    float_t *m;
    QPoint  *vectors;
    float_t max_item;
    QColor  color;
};

#endif //PLAYER_UI_POLYGON_H
