#include "animation.h"
#include "ui_animation.h"

Animation::Animation(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::animation),
    player(player) {
    ui->setupUi(this);
}

Animation::~Animation() {
    delete ui;
}
