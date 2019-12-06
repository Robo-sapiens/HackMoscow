//
// Created by kira on 23.11.2019.
//

#include "polygon.h"
#include <QMutex>
QMutex g_mutex_poly;


Polygon::Polygon(int32_t verteces, int32_t r, int32_t g, int32_t b, float_t radius, int32_t mode) :
    real_vectors(new std::vector<fPoint>(verteces)),
    vectors(new std::vector<QPoint>(verteces)),
    color(r, g, b),
    radius(radius),
    mode(mode),
    rotation(0) {}

Polygon::Polygon(const Polygon &other) :
    real_vectors(new std::vector<fPoint>(other.real_vectors->size())),
    vectors(new std::vector<QPoint>(other.vectors->size())),
    color(other.color),
    radius(other.radius),
    mode(other.mode),
    rotation(other.rotation) {
    for (size_t kI = 0; kI < other.vectors->size(); ++kI) {
        this->real_vectors->at(kI) = other.real_vectors->at(kI);
        this->vectors->at(kI) = other.vectors->at(kI);
    }
}

Polygon::~Polygon() {
    delete real_vectors;
    delete vectors;
}

void Polygon::set_items(const fPoint *matrix) {
    for (size_t kI = 0; kI < vectors->size(); ++kI) {
        real_vectors->at(kI) = matrix[kI];
        vectors->at(kI).setX((int32_t) real_vectors->at(kI).x);
        vectors->at(kI).setY((int32_t) real_vectors->at(kI).y);
    }
}

void Polygon::set_items(const fPoint *matrix, size_t new_size) {
    g_mutex_poly.lock();
    real_vectors->resize(new_size);
    vectors->resize(new_size);
    set_items(matrix);
    g_mutex_poly.unlock();
}

void Polygon::operator*=(const fPoint *tr_matrix) {
    auto tmp_matrix = std::vector<fPoint>(this->real_vectors->begin(), this->real_vectors->end());

    for (size_t j = 0; j < vectors->size(); ++j) {
        real_vectors->at(j).x = tr_matrix[0].x * tmp_matrix.at(j).x + tr_matrix[1].x * tmp_matrix.at(j).y;
        real_vectors->at(j).y = tr_matrix[0].y * tmp_matrix.at(j).x + tr_matrix[1].y * tmp_matrix.at(j).y;
    }

    for (size_t j = 0; j < vectors->size(); ++j) {
        vectors->at(j).setX((int32_t) real_vectors->at(j).x);
        vectors->at(j).setY((int32_t) real_vectors->at(j).y);
    }
}

void Polygon::push_back(fPoint item) {
    real_vectors->push_back(item);
    vectors->push_back(QPoint((int32_t) item.x, (int32_t) item.y));
}

void Polygon::pop_back() {
    real_vectors->pop_back();
    vectors->pop_back();
}
