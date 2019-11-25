#include "main_window.h"
#include "ui_main_window.h"
#include <QPainter>
#include <QDebug>
#include <zconf.h>
#include <cmath>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent, Player *player) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(player),
    base_polygon(),
    polygons(),
    transformation_matrix(new float_t[2 * 2]),
    radius(0) {
    ui->setupUi(this);

    float_t phi = -0.06;
    transformation_matrix[0] = 1.2 * std::cos(phi);
    transformation_matrix[1] = -std::sin(phi);
    transformation_matrix[2] = std::sin(phi);
    transformation_matrix[3] = 1.2 * std::cos(phi);

    float_t matr[10] = {0, 9, 5.5, -5.5, -9, 10, 2, -6.5, -6.5, 2};
    base_polygon.resize(10);
    for (unsigned long kI = 0; kI < base_polygon.size(); ++kI) {
        base_polygon[kI] = matr[kI];
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete[] transformation_matrix;
}

void MainWindow::on_colors_clicked() {
    emit open_colors();
}

void MainWindow::on_devices_clicked() {
    emit open_devices();
}

void MainWindow::on_animation_clicked() {
    emit open_animation();
}

void MainWindow::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate((float) width() / 2, (float) height() / 2);

    auto *tmp = new Polygon(base_polygon.size() / 2,
        player->rgb.r, player->rgb.g, player->rgb.b, radius);
    tmp->set_items(base_polygon.data(), base_polygon.size());
    polygons.push_back(tmp);

    for (auto &polygon : polygons) {
        painter->setBrush(polygon->color);
        painter->setPen(polygon->color);

        if (polygon->radius <= 0) {
            painter->drawPolygon(polygon->vectors, polygon->cols);
            *polygon *= transformation_matrix;
        } else {
            auto center = QPoint(0, 0);
            if (!base_polygon.empty()) {
                center.setX(polygon->vectors->x());
                center.setY(polygon->vectors->y());
            }
            painter->drawEllipse(center, (int32_t)(polygon->radius), (int32_t)(polygon->radius));
            polygon->radius *= 1.2;
        }

        auto last_item = polygons.front();
        if (last_item->max_item > 2 * width()) {
            polygons.pop_front();
            delete last_item;
        }
    }

    usleep(1000000 / player->rgb_parameters.bpm);

    painter->restore();
    delete painter;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_F11) {
        if (this->isFullScreen()) {
            this->showMaximized();
        } else {
            this->showFullScreen();
        }
    }
}

void MainWindow::animation_changed(const float *x, const float *y, int amount, float rad) {
    this->radius = rad;
    base_polygon.resize(amount * 2);
    for (unsigned long kI = 0; kI < amount; ++kI) {
        base_polygon[kI] = x[kI];
    }

    for (unsigned long kJ = 0; kJ < amount; ++kJ) {
        base_polygon[kJ + amount] = y[kJ];
    }
}

void MainWindow::rotation_changed(float rot) {
    transformation_matrix[0] = 1.2 * std::cos(rot);
    transformation_matrix[1] = -std::sin(rot);
    transformation_matrix[2] = std::sin(rot);
    transformation_matrix[3] = 1.2 * std::cos(rot);
}
