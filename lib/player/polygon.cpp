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
    float_t abs = std::sqrt(vectors[0].x * vectors[0].x + vectors[0].y * vectors[0].y);
    if ((vectors[0].x / abs) > (vectors[0].y / abs)) {
        cos = vectors[0].x / abs;
        ind_cos = 0;
    } else {
        cos = vectors[0].y / abs;
        ind_cos = 1;
    }
}

void Polygon::operator*=(const Point *tr_matrix) {
    auto *new_matr = new Point[verteces];

    float_t coef = 0;
    if (ind_cos == 0) {
        coef = (vectors[0].x + cos) / vectors[0].x;
    } else {
        coef = (vectors[0].y + cos) / vectors[0].y;
    }
    for (size_t kI = 0; kI < verteces; ++kI) {
        vectors[kI].x *= coef;
        vectors[kI].y *= coef;
    }
    max_item *= tr_matrix[0].x;
    for (size_t j = 0; j < verteces; ++j) {
        new_matr[j].x = tr_matrix[0].x * vectors[j].x + tr_matrix[1].x * vectors[j].y;
        new_matr[j].y = tr_matrix[0].y * vectors[j].x + tr_matrix[1].y * vectors[j].y;
    }

    delete[] vectors;
    vectors = new_matr;

}
