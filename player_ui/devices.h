#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class devices; }
QT_END_NAMESPACE

class Devices : public QWidget
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = nullptr, Player *player = nullptr);
    ~Devices();

private:
    Ui::devices *ui;
    Player * player;
};

#endif // DEVICES_H
