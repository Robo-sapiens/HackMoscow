#include <unistd.h>
#include "animationpresettings.h"
#include "ui_animationpresettings.h"
#include <QDebug>


AnimationPreSettings::AnimationPreSettings(QWidget *parent, Player *player) :
    QWidget(parent),
    animation_(Animation(nullptr, player)),
    ui(new Ui::AnimationPreSettings),
    _player(player){
    ui->setupUi(this);
    QObject::connect(ui->buttonAdvanced, SIGNAL(clicked()), &animation_, SLOT(show()));
    QObject::connect(ui->buttonSubmit, SIGNAL(clicked()), &animation_, SLOT(on_buttonSubmit_clicked()));
    QObject::connect(this, SIGNAL(new_mode(int)), &animation_, SLOT(on_new_mode(int)));
    emit new_mode(2);
}

AnimationPreSettings::~AnimationPreSettings() {
    delete ui;
}

void AnimationPreSettings::on_buttonSetWL_clicked() {
    auto tmpwidth = ui->editWidth->toPlainText().toInt();
    auto tmplength = ui->editLength->toPlainText().toInt();
    if (tmplength > 0 && tmpwidth > 0) {
        _player->msg.set_new_led(tmpwidth, tmplength);
        usleep(500000);
        _player->msg.set_default();
    }
}

void AnimationPreSettings::on_selectMode_currentIndexChanged(int index) {
    if (index >= 0 && index <= 2) {
        emit new_mode(index);
    }
}
