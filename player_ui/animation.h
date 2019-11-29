#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"
#include "polygon.h"
#include "presets.h"
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
    void change_verteces(int verteces, const fPoint *vectors, float radius, int mode);
    void change_rotation(float rot);

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_value_changed();
    void on_checkCircle_stateChanged(int arg1);
    void on_editRadius_textChanged();
    void on_editRotation_textChanged();
    void on_buttonSubmit_clicked();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::animation *ui;
    Player *player;
    std::vector<std::pair<QTextEdit *, QTextEdit *>> *vertices;
    Polygon *base_polygon;
    AnimationPresets *presets;
};

#endif // ANIMATION_H
