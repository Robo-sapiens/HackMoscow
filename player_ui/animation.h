#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"
#include <QWidget>
#include <utility>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class animation; }
QT_END_NAMESPACE

class Animation : public QWidget {
Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr, Player *player = nullptr);
    ~Animation() override;

signals:
    void change_verteces(float *x, float *y, int amount, float radius);

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_value_changed();

    void on_checkCircle_stateChanged(int arg1);

    void on_editRadius_textChanged();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::animation *ui;
    Player *player;
    std::vector<std::pair<QTextEdit *, QTextEdit *>> *vertices;
    int32_t amount;
    std::vector<float> *x;
    std::vector<float> *y;
    float radius;
};

#endif // ANIMATION_H
