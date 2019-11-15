#include "color.h"
#include "ui_color.h"

Color::Color(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::color),
    player(player)

{
    ui->setupUi(this);
}

Color::~Color()
{
    delete ui;
}
