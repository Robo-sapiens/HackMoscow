#include "devices.h"
#include "ui_devices.h"
#include <QSerialPortInfo>
#include "capture.h"


Devices::Devices(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::devices),
    player(player),
    sound_card_list(new QStringListModel(this)),
    ports_list(new QStringListModel(this)) {

    ui->setupUi(this);
    load_cards();
    load_ports();
}

Devices::~Devices() {
    delete ui;
    delete sound_card_list;
    delete ports_list;
}

void Devices::on_select_card_clicked() {
    player->capture_device.isSet = false;
    player->capture_device.set_device(ui->soundCardList->currentIndex().data().toString().toUtf8().data());
    emit start_capture();
}

void Devices::on_select_port_clicked() {
    if (ui->portsList->currentIndex().data().toString() != "") {
        emit start_port(QSerialPortInfo::availablePorts()[ui->soundCardList->currentIndex().data().toInt()]);
    }
}

void Devices::load_ports() {
    QStringList portStringList;
    for (int i = 0; i < QSerialPortInfo::availablePorts().length(); ++i) {
        portStringList << QSerialPortInfo::availablePorts()[i].portName();
    }
    ports_list->setStringList(portStringList);
    ui->portsList->setModel(ports_list);
}

void Devices::load_cards() {
    QStringList deviceStringList;
    deviceStringList << "WIP";
    //TODO
    sound_card_list->setStringList(deviceStringList);
    ui->soundCardList->setModel(sound_card_list);
}
