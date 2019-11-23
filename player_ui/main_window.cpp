#include "main_window.h"
#include "ui_main_window.h"
#include <QPainter>
#include <QDebug>
#include <zconf.h>

MainWindow::MainWindow(QWidget *parent, Player * player)
        : QMainWindow(parent),
          ui(new Ui::MainWindow),
          player(player),
          polygons() {
    ui->setupUi(this);
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
        *polygon *= 1.2;
//        *polygon += 10;
        auto last_item = polygons.front();
        if (last_item->max_item > 2 * width()) {
            polygons.pop_front();
            delete last_item;
        }
    }

    usleep(500000 / player->rgb_parameters.bpm);

    auto * tmp = new Polygon(3, player->rgb.r, player->rgb.g, player->rgb.b);
    double matrix[6] = {-10, 10, 0, 10, 10, -10};
    tmp->set_items(matrix, 6);
    polygons.push_back(tmp);

    painter->restore();
    delete painter;
}
