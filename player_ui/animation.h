#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class animation; }
QT_END_NAMESPACE

class Animation : public QWidget
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr, Player *player = nullptr);
    ~Animation();

private:
    Ui::animation *ui;
    Player * player;
};

#endif // ANIMATION_H
