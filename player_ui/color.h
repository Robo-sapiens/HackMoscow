#ifndef COLOR_H
#define COLOR_H

#include <QWidget>
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class color; }
QT_END_NAMESPACE

class Color : public QWidget
{
    Q_OBJECT

public:
    explicit Color(QWidget *parent = nullptr, Player *player = nullptr);
    ~Color();

private:
    Ui::color *ui;
    Player *player;
};

#endif // COLOR_H
