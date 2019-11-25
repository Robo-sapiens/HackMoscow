#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <player.h>
#include "polygon.h"
#include <deque>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, Player *player = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void open_colors();
    void open_animation();
    void open_devices();

public slots:
    void animation_changed(const float *x, const float *y, int amount, float rad);
    void rotation_changed(float rot);

private slots:
    void on_colors_clicked();
    void on_devices_clicked();
    void on_animation_clicked();

//    void on_MainWindow_destroyed();

private:
    Ui::MainWindow *ui;
    Player *player;
    std::vector<float_t> base_polygon;
    std::deque<Polygon *> polygons;
    float_t *transformation_matrix;
    float_t radius;
};

#endif // MAINWINDOW_H
