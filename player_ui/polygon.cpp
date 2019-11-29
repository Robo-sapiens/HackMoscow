//
// Created by kira on 23.11.2019.
//

#include "polygon.h"
#include <QDebug>

Polygon::Polygon(size_t verteces, int32_t r, int32_t g, int32_t b, float_t radius, int32_t mode) :
    verteces(verteces),
    real_vectors(new std::vector<fPoint>(verteces)),
    vectors(new std::vector<QPoint>(verteces)),
    max_item(0),
    color(r, g, b),
    radius(radius),
    mode(mode),
    rotation(0) {}

Polygon::Polygon(const Polygon &other) :
    verteces(other.verteces),
    real_vectors(new std::vector<fPoint>(verteces)),
    vectors(new std::vector<QPoint>(verteces)),
    max_item(other.max_item),
    color(other.color),
    radius(other.radius),
    mode(other.mode),
    rotation(other.rotation) {
    for (size_t kI = 0; kI < verteces; ++kI) {
        this->real_vectors->at(kI) = other.real_vectors->at(kI);
        this->vectors->at(kI) = other.vectors->at(kI);
    }
}

Polygon::~Polygon() {
    delete real_vectors;
    delete vectors;
}

void Polygon::set_items(const fPoint *matrix) {
    for (size_t kI = 0; kI < verteces; ++kI) {
        real_vectors->at(kI) = matrix[kI];
        vectors->at(kI).setX((int32_t)real_vectors->at(kI).x);
        vectors->at(kI).setY((int32_t)real_vectors->at(kI).y);
        max_item = std::max(max_item, std::max(std::abs(real_vectors->at(kI).x), std::abs(real_vectors->at(kI).y)));
    }
}

void Polygon::operator*=(const fPoint *tr_matrix) {
    auto new_matrix = new std::vector<fPoint>(verteces);

    for (size_t j = 0; j < verteces; ++j) {
        new_matrix->at(j).x = tr_matrix[0].x * real_vectors->at(j).x + tr_matrix[1].x * real_vectors->at(j).y;
        new_matrix->at(j).y = tr_matrix[0].y * real_vectors->at(j).x + tr_matrix[1].y * real_vectors->at(j).y;
    }

    delete real_vectors;
    real_vectors = new_matrix;
    for (size_t j = 0; j < verteces; ++j) {
        vectors->at(j).setX((int32_t)real_vectors->at(j).x);
        vectors->at(j).setY((int32_t)real_vectors->at(j).y);
    }
    max_item *= tr_matrix[0].x;
}

void Polygon::push_back(fPoint item) {
    ++verteces;
    real_vectors->push_back(item);
    vectors->push_back(QPoint((int32_t)item.x, (int32_t)item.y));
    max_item = std::max(max_item, std::max(std::abs(item.x), std::abs(item.y)));
}

void Polygon::pop_back() {
    --verteces;
    real_vectors->pop_back();
    vectors->pop_back();
    for (size_t kI = 0; kI < verteces; ++kI) {
        max_item = std::max(max_item, std::max(std::abs(real_vectors->at(kI).x), std::abs(real_vectors->at(kI).y)));
    }
}
