//
// Created by kira on 15.11.2019.
//

#ifndef PLAYER_UI_DEVICE_INTERFACE_H
#define PLAYER_UI_DEVICE_INTERFACE_H

#include <QSerialPort>

class device_interface {
public:
    device_interface();
    ~device_interface();

private:
    QSerialPort *serial_port;
};


#endif //PLAYER_UI_DEVICE_INTERFACE_H
