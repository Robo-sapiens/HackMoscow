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
    base_polygon(new Polygon(5, 0, 0, 0)),
    polygons(new std::deque<Polygon>),
    transformation_matrix(new fPoint[2]) {
    ui->setupUi(this);

    float_t phi = -0.06;
    transformation_matrix[0].x = 1.2f * std::cos(phi);
    transformation_matrix[0].y = std::sin(phi);
    transformation_matrix[1].x = -std::sin(phi);
    transformation_matrix[1].y = 1.2f * std::cos(phi);

    fPoint base_matrix[5] = {10, 0, 3.09, -9.51, -8.09, -5.88, -8.09, 5.88, 3.09, 9.51};
    base_polygon->set_items(base_matrix);
}

MainWindow::~MainWindow() {
    delete ui;
    delete base_polygon;
    delete polygons;
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

    auto tmp = Polygon(*base_polygon);
    tmp.color = QColor(player->rgb.r, player->rgb.g, player->rgb.b);
    polygons->push_back(tmp);

    for (auto &polygon: *polygons) {
        painter->setBrush(polygon.color);
        painter->setPen(polygon.color);

        if (polygon.mode == 0) {
            painter->drawPolygon(polygon.vectors->data(), polygon.verteces);
            polygon *= transformation_matrix;
        } else if (polygon.mode == 1) {
            auto center = QPoint(0, 0);
            if (base_polygon->verteces > 0) {
                center.setX(polygon.vectors->data()->x());
                center.setY(polygon.vectors->data()->y());
            }
            painter->drawEllipse(center, (int32_t) (polygon.radius), (int32_t) (polygon.radius));
            polygon.radius *= 1.2;
        }

    }
    while (polygons->size() > 49) {
        auto last_item = polygons->front();
        polygons->pop_front();
//        delete last_item;
    }

    painter->restore();
    delete painter;
}

void MainWindow::animation_changed(int verteces, const fPoint *vectors, float radius, int mode) {
    delete base_polygon;
    base_polygon = new Polygon(verteces, 0, 0, 0, radius, mode);
    base_polygon->set_items(vectors);
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

void MainWindow::rotation_changed(float rot) {
    base_polygon->rotation = rot;
    transformation_matrix[0].x = 1.2f * std::cos(rot);
    transformation_matrix[0].y = std::sin(rot);
    transformation_matrix[1].x = -std::sin(rot);
    transformation_matrix[1].y = 1.2f * std::cos(rot);
}
