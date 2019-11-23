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


class Polygon
{
public:
    Polygon(size_t verteces, int32_t r, int32_t g, int32_t b);
    Polygon(const Polygon & other);
    ~Polygon();

    void set_items(const double *matrix, size_t size);
    double * operator()(size_t row, size_t col);
    void rotate(double rad);
    void operator*=(double coef);

    size_t rows;
    size_t cols;
    double *m;
    QPoint *vectors;
    double max_item;
    QColor color;
};


#endif //PLAYER_UI_POLYGON_H
