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
    ~Color() override;

private slots:

    void on_sliderWidth_valueChanged(int value);
    void on_sliderRed_valueChanged(int value);
    void on_sliderGreen_valueChanged(int value);
    void on_sliderBlue_valueChanged(int value);
    void on_nobSensitivity_valueChanged(int value);
    void on_nobFilter_valueChanged(int value);
    void on_checkMinFilter_stateChanged(int arg1);
    void on_buttonReset_clicked();
    void on_nobBPM_valueChanged(int value);
    void on_editBPM_textChanged();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::color *ui;
    Player *player;
    QPoint *qpoints;

};

#endif // COLOR_H
