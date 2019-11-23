#include "main_window.h"
#include "ui_main_window.h"
#include <QPainter>
#include <QDebug>
#include <zconf.h>
#include <cmath>

MainWindow::MainWindow(QWidget *parent, Player * player)
        : QMainWindow(parent),
          ui(new Ui::MainWindow),
          player(player),
          polygons(),
          transformation_matrix(new double[2 * 2]) {
    ui->setupUi(this);
    double phi = -0.06;
    transformation_matrix[0] = 1.2 * std::cos(phi);
    transformation_matrix[1] = -std::sin(phi);
    transformation_matrix[2] = std::sin(phi);
    transformation_matrix[3] = 1.2 * std::cos(phi);
}

MainWindow::~MainWindow() {
    delete ui;
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
    painter->translate((float)width() / 2, (float)height() / 2);

    for (auto & polygon : polygons) {
        painter->setBrush(polygon->color);
        painter->setPen(polygon->color);
        painter->drawPolygon(polygon->vectors, polygon->cols);
        *polygon *= transformation_matrix;
        auto last_item = polygons.front();
        if (last_item->max_item > 2 * width()) {
            polygons.pop_front();
            delete last_item;
        }
    }

    usleep(500000 / player->rgb_parameters.bpm);

    auto * tmp = new Polygon(5, player->rgb.r, player->rgb.g, player->rgb.b);
    double matrix[10] = {0, 9, 5, -5, -9, 10, 2, -6, -6, 2};
    tmp->set_items(matrix, 10);
    polygons.push_back(tmp);

    painter->restore();
    delete painter;
}
