#include "main_window.h"
#include "ui_main_window.h"
#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QKeyEvent>
#include <unistd.h>


MainWindow::MainWindow(QWidget *parent, Player *player) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(player),
    base_polygon(new Polygon(5, 0, 0, 0)),
    polygons(new fixed_queue<Polygon *, POLYGON_AMOUNT>),
    transformation_matrix(new fPoint[2]) {
    ui->setupUi(this);

    float_t phi = -0.1;
    transformation_matrix[0].x = 1.3f * std::cos(phi);
    transformation_matrix[0].y = std::sin(phi);
    transformation_matrix[1].x = -std::sin(phi);
    transformation_matrix[1].y = 1.3f * std::cos(phi);

    fPoint base_matrix[5] = {1, 0, 0.3, -0.9, -0.8, -0.6, -0.8, 0.6, 0.3, 0.9};
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

    auto tmp = new Polygon(*base_polygon);
    tmp->color = QColor(player->rgb.r, player->rgb.g, player->rgb.b);
    polygons->push_back(tmp);

    for (unsigned kI = 0; kI < polygons->size(); ++kI) {
        auto polygon = polygons->at(kI);
        painter->setBrush(polygon->color);
        painter->setPen(polygon->color);

        if (polygon->mode == 0) {
            painter->drawPolygon(polygon->vectors->data(), polygon->vectors->size());
            *polygon *= transformation_matrix;
        } else if (polygon->mode == 1) {
            auto center = QPoint(0, 0);
            if (!base_polygon->vectors->empty()) {
                center.setX(polygon->vectors->data()->x());
                center.setY(polygon->vectors->data()->y());
            }
            painter->drawEllipse(center, (int32_t) (polygon->radius), (int32_t) (polygon->radius));
            polygon->radius *= 1.2;
        }

    }
    usleep(800000 / player->rgb_parameters.bpm);
    painter->restore();
    delete painter;
}

void MainWindow::animation_changed(int verteces, const fPoint *vectors, float radius, int mode) {
    if (mode == 2) {
        return;
    }
    delete base_polygon;
    base_polygon = new Polygon(verteces, 0, 0, 0, 10 * radius, mode);
    fPoint tmp_vectors[verteces];
    for (int kI = 0; kI < verteces; ++kI) {
        tmp_vectors[kI].x = 16 * vectors[kI].x;
        tmp_vectors[kI].y = 16 * vectors[kI].y;
    }
    base_polygon->set_items(tmp_vectors);
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
    transformation_matrix[0].x = 1.3f * std::cos(rot);
    transformation_matrix[0].y = std::sin(rot);
    transformation_matrix[1].x = -std::sin(rot);
    transformation_matrix[1].y = 1.3f * std::cos(rot);
}
