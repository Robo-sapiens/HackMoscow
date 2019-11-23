#include "main_window.h"
#include "ui_main_window.h"
#include <QPainter>
#include <QDebug>
#include <cstdlib>
#include <zconf.h>

MainWindow::MainWindow(QWidget *parent, Player * player)
        : QMainWindow(parent),
          ui(new Ui::MainWindow),
          player(player),
          polygon(new Polygon(3, 100, 0, 0))
          {
    ui->setupUi(this);
//    auto * tmp = new Polygon(3, 100, 0, 0);
    double matrix[6] = {-1, 1, 0, 1, 1, -1};
    polygon->set_items(matrix, 6);
//    polygons->push(tmp);
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
    painter->setBrush(polygon->color);
    painter->drawPolygon(polygon->vectors, polygon->cols);
    *polygon *= 1.1;
    usleep(80000);
    qDebug() << *polygon->vectors;
    if (polygon->max_item > width()) {
        qDebug() << "finished";
    }
    painter->restore();
    delete painter;
}