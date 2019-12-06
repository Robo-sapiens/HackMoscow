#include "animation.h"
#include "ui_animation.h"
#include <QDebug>
#include <QPainter>
#include <zconf.h>


Animation::Animation(QWidget *parent, Player *player) :
    QWidget(parent),
    base_polygon(new Polygon(0, 0, 0, 0)),
    ui(new Ui::animation),
    player(player),
    vertices(new std::vector<std::pair<QTextEdit *, QTextEdit *>>),
    presets(new AnimationPresets) {
    ui->setupUi(this);
    // presets window
    QObject::connect(ui->buttonPresets, SIGNAL(clicked()), presets, SLOT(show()));
    presets->set_params(base_polygon);
    on_spinBox_valueChanged(1);
    ui->editRadius->setPlainText("1");
}

Animation::~Animation() {
    delete ui;
    while (!vertices->empty()) {
        auto tmp = vertices->back();
        vertices->pop_back();
        delete tmp.first;
        delete tmp.second;
    }
    delete vertices;
    delete base_polygon;
    delete presets;
}

void Animation::on_spinBox_valueChanged(int arg1) {
    while (arg1 > base_polygon->vectors->size()) {
        auto t1 = new QTextEdit();
        auto t2 = new QTextEdit();
        t1->setFixedSize(71, 27);
        t2->setFixedSize(71, 27);
        t1->setPlainText("0");
        t2->setPlainText("0");
        QObject::connect(t1, SIGNAL(textChanged()), this, SLOT(on_value_changed()));
        QObject::connect(t2, SIGNAL(textChanged()), this, SLOT(on_value_changed()));
        vertices->push_back({t1, t2});
        ui->mainLayout->addWidget(t1, (int32_t) base_polygon->vectors->size() + 4, 0);
        ui->mainLayout->addWidget(t2, (int32_t) base_polygon->vectors->size() + 4, 1);
        base_polygon->push_back({0, 0});
    }
    while (arg1 < base_polygon->vectors->size()) {
        auto tmp = vertices->back();
        vertices->pop_back();
        delete tmp.first;
        delete tmp.second;
        base_polygon->pop_back();
    }
}

void Animation::on_value_changed() {
    fPoint new_matrix[base_polygon->vectors->size()];
    for (size_t kI = 0; kI < base_polygon->vectors->size(); ++kI) {
        if (std::abs(vertices->at(kI).first->toPlainText().toFloat()) > 20) {
            vertices->at(kI).first->setText("20");
        }
        if (std::abs(vertices->at(kI).second->toPlainText().toFloat()) > 20) {
            vertices->at(kI).second->setText("20");
        }
        new_matrix[kI].x = vertices->at(kI).first->toPlainText().toFloat();
        new_matrix[kI].y = vertices->at(kI).second->toPlainText().toFloat();
    }
    base_polygon->set_items(new_matrix);
}

void Animation::on_editRadius_textChanged() {
    auto text_tmp = ui->editRadius->toPlainText();
    if (text_tmp != "" && text_tmp.toFloat() > 0) {
        base_polygon->radius = text_tmp.toFloat();
    }
}

void Animation::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate((float) ui->spinBox->x() / 2,
                       (float) height() / 2);

    painter->setBrush(QColor(player->rgb.r, player->rgb.g, player->rgb.b));
    painter->setPen(QColor(player->rgb.r, player->rgb.g, player->rgb.b));

    if (base_polygon->mode == 0) {
        auto points = new QPoint[base_polygon->vectors->size()];
        for (size_t kI = 0; kI < base_polygon->vectors->size(); ++kI) {
            points[kI].setX((int32_t) (base_polygon->real_vectors->at(kI).x * 64));
            points[kI].setY((int32_t) (base_polygon->real_vectors->at(kI).y * -64));
        }
        painter->drawPolygon(points, base_polygon->vectors->size());
        delete[] points;
    } else if (base_polygon->mode == 1) {
        auto center = QPoint(0, 0);
        if (!base_polygon->vectors->empty()) {
            center.setX(base_polygon->vectors->data()->x());
            center.setY(base_polygon->vectors->data()->y());
        }
        painter->drawEllipse(center, (int32_t) (base_polygon->radius * 64), (int32_t) (base_polygon->radius * 64));
    }

    painter->setBrush(Qt::white);
    painter->setPen(Qt::white);
    painter->drawEllipse(QPoint(0, 0), 2, 2);

    painter->restore();
    delete painter;
}

void Animation::on_buttonSubmit_clicked() {
    // mode == 0 => polygon
    // mode == 1 => circle
    // mode == 2 => basic
    float_t x[std::max(1ul, base_polygon->vectors->size())];
    float_t y[std::max(1ul, base_polygon->vectors->size())];
    int32_t verteces = 0;
    if (base_polygon->mode == 0) {
        verteces = base_polygon->vectors->size();
        for (size_t kI = 0; kI < verteces; ++kI) {
            x[kI] = base_polygon->real_vectors->at(kI).x;
            y[kI] = base_polygon->real_vectors->at(kI).y;
        }
    } else if (base_polygon->mode == 1) {
        verteces = 1;
        if (base_polygon->vectors->empty()) {
            x[0] = 0;
            y[0] = 0;
        } else {
            x[0] = base_polygon->real_vectors->data()->x;
            y[0] = base_polygon->real_vectors->data()->y;
        }
    }
    player->msg.set_settings(base_polygon->mode, verteces, x, y,
                             player->rgb_parameters.bpm, base_polygon->rotation);
    usleep(500000);
    player->msg.set_default();
    emit change_verteces(base_polygon->vectors->size(), base_polygon->real_vectors->data(),
                         base_polygon->radius, base_polygon->mode);
}

void Animation::on_editRotation_textChanged() {
    auto text_tmp = ui->editRotation->toPlainText();
    if (text_tmp != "") {
        if (std::abs(text_tmp.toFloat()) > 20) {
            ui->editRotation->setText("20");
        }
        emit change_rotation((float_t) (ui->editRotation->toPlainText().toDouble() * M_PI / 180));
    }
}

void Animation::on_new_mode(int mode) {
    // mode == 0 - polygon
    // mode == 1 - circle
    // mode == 2 - basic
    qDebug() << mode;
    base_polygon->mode = mode;
    if (mode == 0) {
        ui->editRadius->setDisabled(true);
        ui->radius->setDisabled(true);
        ui->spinBox->setEnabled(true);
        ui->editRotation->setEnabled(true);
        for (auto &vector : *vertices) {
            vector.first->setEnabled(true);
            vector.second->setEnabled(true);
        }
    } else if (mode == 1) {
        ui->editRadius->setEnabled(true);
        ui->radius->setEnabled(true);
        ui->editRotation->setDisabled(true);
        vertices->at(0).first->setEnabled(true);
        vertices->at(0).second->setEnabled(true);
        vertices->at(0).first->update();
        vertices->at(0).second->update();
        for (size_t kI = 1; kI < vertices->size(); ++kI) {
            vertices->at(kI).first->setDisabled(true);
            vertices->at(kI).second->setDisabled(true);
        }
    } else if (mode == 2) {
        ui->editRadius->setDisabled(true);
        ui->radius->setDisabled(true);
        ui->spinBox->setDisabled(true);
        ui->editRotation->setDisabled(true);
        for (auto &vector : *vertices) {
            vector.first->setDisabled(true);
            vector.second->setDisabled(true);
        }
    }
}
