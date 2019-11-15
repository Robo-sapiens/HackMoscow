#include "main_window.h"
#include "./ui_main_window.h"
#define DELAY 60000
#define DEVICE "/dev/ttyACM0"
#define SAMPLE_SIZE 512  // connected to BASS_FFT_1024

MainWindow::MainWindow(QWidget *parent, Player * player)
: QMainWindow(parent),
ui(new Ui::MainWindow),
player(player) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_colors_clicked() {
    emit open_colors();
}

void MainWindow::on_devices_clicked() {
    emit open_devices();
}

void MainWindow::on_animation_clicked() {
    emit open_animation();
}
