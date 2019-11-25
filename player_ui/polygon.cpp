//
// Created by kira on 23.11.2019.
//

#include "polygon.h"

Polygon::Polygon(size_t verteces, int32_t r, int32_t g, int32_t b, float_t radius) :
    rows(2), cols(verteces), m(new float_t[rows * cols]),
    vectors(new QPoint[cols]), max_item(0), color(r, g, b), radius(radius) {}

Polygon::Polygon(const Polygon &other) :
    rows(other.rows), cols(other.cols), m(new float_t[rows * cols]),
    vectors(new QPoint[cols]), max_item(other.max_item), color(other.color) {
    for (size_t i = 0; i < rows * cols; ++i) {
        this->m[i] = other.m[i];
    }

    for (size_t j = 0; j < cols; ++j) {
        vectors[j] = other.vectors[j];
    }
}

Polygon::~Polygon() {
    delete[] m;
    delete[] vectors;
}

void Polygon::set_items(const float_t *matrix, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        m[i] = matrix[i];
        max_item = std::max(max_item, std::abs(m[i]));
    }

    for (size_t j = 0; j < cols; ++j) {
        vectors[j].setX((int) *this->operator()(0, j));
        vectors[j].setY((int) *this->operator()(1, j));
    }
}

float_t *Polygon::operator()(size_t row, size_t col) {
    return &m[row * cols + col];
}

void Polygon::operator*=(float_t coef) {
    for (size_t i = 0; i < rows * cols; ++i) {
        m[i] *= coef;
    }

    for (size_t j = 0; j < cols; ++j) {
        vectors[j].setX((int) (*this->operator()(0, j)));
        vectors[j].setY((int) (*this->operator()(1, j)));
    }

    max_item *= coef;
}

void Polygon::operator*=(const float_t *tr_matrix) {
    auto *new_matr = new float_t[rows * cols];

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr[i * cols + j] = tr_matrix[i * rows + 0] * m[/*0 * cols + */ j] +
                tr_matrix[i * rows + 1] * m[/*1 * */cols + j];
        }
    }

    delete[] m;
    m = new_matr;

    for (size_t j = 0; j < cols; ++j) {
        vectors[j].setX((int) (*this->operator()(0, j)));
        vectors[j].setY((int) (*this->operator()(1, j)));
    }

    max_item *= tr_matrix[0];
}
