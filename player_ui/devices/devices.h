#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>
#include <QtCore/QStringListModel>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "player.h"
#include "capture.h"


QT_BEGIN_NAMESPACE
namespace Ui { class devices; }
QT_END_NAMESPACE

class Devices : public QWidget {
Q_OBJECT

public:
    explicit Devices(QWidget *parent = nullptr, Player *player = nullptr);
    ~Devices();

private:
    void load_ports();
    void load_cards();

private slots:
    void on_select_card_clicked();
    void on_select_port_clicked();

signals:
    void start_capture();
    void start_port(const QSerialPortInfo &q_serial_port_info);

private:
    Ui::devices *ui;
    Player *player;
    QStringListModel *sound_card_list;
    QStringListModel *ports_list;
};


#endif // DEVICES_H
