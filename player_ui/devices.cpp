#include "devices.h"
#include "ui_devices.h"

Devices::Devices(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::devices),
    player(player)
{
    ui->setupUi(this);
}

Devices::~Devices()
{
    delete ui;
}
