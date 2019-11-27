//
// Created by kira on 27.11.2019.
//

#include "polygon.h"

Polygon::Polygon(size_t verteces, int32_t r, int32_t g, int32_t b) :
    verteces(verteces),
    vectors(new Point[verteces]),
    max_item(0),
    color({r, g, b}) {
    if (verteces == 0) {
        this->verteces = 1;
        radius = 1;
    } else {
        radius = 0;
    }
}

Polygon::~Polygon() {
    delete[] vectors;
}

void Polygon::set_items(const Point *matrix, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        vectors[i] = matrix[i];
        max_item = std::max(max_item, std::max(std::abs(vectors[i].x), std::abs(vectors[i].y)));
    }
}

void Polygon::operator*=(const Point *tr_matrix) {
    auto *new_matr = new Point[verteces];

    for (size_t j = 0; j < verteces; ++j) {
        new_matr[j].x = tr_matrix[0].x * vectors[j].x + tr_matrix[1].x * vectors[j].y;
        new_matr[j].y = tr_matrix[0].y * vectors[j].x + tr_matrix[1].y * vectors[j].y;
    }

    delete[] vectors;
    vectors = new_matr;

    max_item *= tr_matrix[0].x;
}
