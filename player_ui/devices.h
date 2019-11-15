#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>
#include <QtCore/QStringListModel>
#include <QSerialPort>
#include "player.h"
#include "device_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class devices; }
QT_END_NAMESPACE

class Devices : public QWidget
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = nullptr, Player *player = nullptr);
    ~Devices();

private slots:
    void on_select_card_clicked();
    void on_select_port_clicked();

private:
    Ui::devices *ui;
    Player *player;
    QStringListModel *sound_card_list;
    QStringListModel *ports_list;
    DeviceInterface serial_device;
};

#endif // DEVICES_H
