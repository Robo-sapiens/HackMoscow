//
// Created by kira on 15.11.2019.
//

#include "device_interface.h"
#include <QSerialPortInfo>

device_interface::device_interface()
: serial_port(new QSerialPort()) {
    serial_port->setBaudRate(QSerialPort::Baud19200);
    serial_port->setDataBits(QSerialPort::Data8);
    serial_port->setParity(QSerialPort::NoParity);
    serial_port->setStopBits(QSerialPort::OneStop);
    serial_port->setFlowControl(QSerialPort::NoFlowControl);
}

device_interface::~device_interface() {
    serial_port->close();
    delete serial_port;
}
