#include "animation.h"
#include "ui_animation.h"
#include <QDebug>
#include <QPainter>

Animation::Animation(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::animation),
    player(player),
    vertices(new std::vector<std::pair<QTextEdit *, QTextEdit *>>),
    amount(0),
    x(new std::vector<float>),
    y(new std::vector<float>),
    radius(-1.f)
    {
    ui->setupUi(this);
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
    delete x;
    delete y;
}

void Animation::on_spinBox_valueChanged(int arg1) {
    while (arg1 > amount) {
        auto t1 = new QTextEdit();
        auto t2 = new QTextEdit();
        t1->setFixedSize(71, 27);
        t2->setFixedSize(71, 27);
        t1->setPlainText("1");
        t2->setPlainText("1");
        QObject::connect(t1, SIGNAL(textChanged()), this, SLOT(on_value_changed()));
        QObject::connect(t2, SIGNAL(textChanged()), this, SLOT(on_value_changed()));
        vertices->push_back({t1, t2});
        ui->mainLayout->addWidget(t1, amount + 3, 0);
        ui->mainLayout->addWidget(t2, amount + 3, 1);
        x->push_back(1);
        y->push_back(1);
        ++amount;
    }

    while (arg1 < amount) {
        auto tmp = vertices->back();
        vertices->pop_back();
        delete tmp.first;
        delete tmp.second;
        x->pop_back();
        y->pop_back();
        --amount;
    }
}


void Animation::on_value_changed() {
    for (int32_t kI = 0; kI < amount; ++kI) {
        x->at(kI) = vertices->at(kI).first->toPlainText().toFloat();
        y->at(kI) = vertices->at(kI).second->toPlainText().toFloat();
    }
}

void Animation::on_checkCircle_stateChanged(int arg1) {
    if (arg1) {
        auto text_tmp = ui->editRadius->toPlainText();
        if (text_tmp != "" && text_tmp.toFloat() > 0) {
            radius = ui->editRadius->toPlainText().toFloat();
        } else {
            radius = 1.f;
        }
    } else {
        radius = -1;
    }
    // TODO: emit
}

void Animation::on_editRadius_textChanged() {
    auto text_tmp = ui->editRadius->toPlainText();
    if (text_tmp != "" && text_tmp.toFloat() > 0) {
        radius = ui->editRadius->toPlainText().toFloat();
    }
}

void Animation::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate((float)ui->checkCircle->x() / 2,
                       (float)height() / 2);

    painter->setBrush(QColor(player->rgb.r, player->rgb.g, player->rgb.b));
    painter->setPen(QColor(player->rgb.r, player->rgb.g, player->rgb.b));

    if (radius >= 0) {
        auto center = new QPoint(0, 0);
        if (!x->empty() && !y->empty()) {
            center->setX(x->front());
            center->setY(-y->front());
        }
        painter->drawEllipse(*center, (int32_t)(radius * 20), (int32_t)(radius * 20));
    } else {
        auto points = new QPoint[amount];
        for (int32_t kI = 0; kI < amount; ++kI) {
            points[kI].setX((int32_t) (x->at(kI) * 20));
            points[kI].setY((int32_t) (y->at(kI) * -20));
        }
        painter->drawPolygon(points, amount);

        delete[] points;
    }

    painter->setBrush(Qt::white);
    painter->setPen(Qt::white);
    painter->drawEllipse(QPoint(0, 0), 2, 2);

    painter->restore();
    delete painter;
}
