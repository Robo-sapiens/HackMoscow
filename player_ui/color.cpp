#include "color.h"
#include "ui_color.h"
#include <QtMath>
#include <QDebug>
#include <QPainter>

Color::Color(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::color),
    player(player),
    qpoints(new QPoint[player->msg.sample_size]) {
    //TODO: advanced settings
    ui->setupUi(this);
    ui->sliderBlue->setRange(0, player->msg.sample_size / 2 - 1);
    ui->sliderGreen->setRange(0, player->msg.sample_size / 2 - 1);
    ui->sliderRed->setRange(0, player->msg.sample_size / 2 - 1);
    ui->sliderWidth->setRange(0, player->msg.sample_size / 2 - 1);
    ui->nobSensitivity->setRange(-50, 50);
    ui->nobFilter->setRange(0, 400);
    ui->nobBPM->setRange(30, 240);
    ui->nobImpactR->setRange(0, 400);
    ui->nobImpactG->setRange(0, 400);
    ui->nobImpactB->setRange(0, 400);

    ui->sliderBlue->setSliderPosition(player->rgb_parameters.blue_peak);
    ui->sliderGreen->setSliderPosition(player->rgb_parameters.green_peak);
    ui->sliderRed->setSliderPosition(player->rgb_parameters.red_peak);
    ui->sliderWidth->setSliderPosition(player->rgb_parameters.width);
    ui->checkMinFilter->setCheckState(Qt::CheckState(((int)player->rgb_parameters.tweak_by_min) * 2));
    ui->nobBPM->setSliderPosition(player->rgb_parameters.bpm);
    ui->nobImpactR->setSliderPosition(400);
    ui->nobImpactG->setSliderPosition(400);
    ui->nobImpactB->setSliderPosition(400);
}

Color::~Color() {
    delete ui;
    delete[] qpoints;
}

void Color::on_sliderWidth_valueChanged(int value) {
    player->rgb_parameters.width = value;
}

void Color::on_sliderRed_valueChanged(int value) {
    player->rgb_parameters.red_peak = value;
}

void Color::on_sliderGreen_valueChanged(int value) {
    player->rgb_parameters.green_peak = value;
}

void Color::on_sliderBlue_valueChanged(int value) {
    player->rgb_parameters.blue_peak = value;
}

void Color::on_nobSensitivity_valueChanged(int value) {
    player->rgb_parameters.sensitivity = 255. / 5000 * qPow(2, (double) value / 20); // 1..INF
}

void Color::on_nobFilter_valueChanged(int value) {
    player->rgb_parameters.filter = value / 400;
}

void Color::on_checkMinFilter_stateChanged(int arg1) {
    player->rgb_parameters.tweak_by_min = arg1;
}

void Color::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate(ui->sliderBlue->x(),
                       (float) (ui->sliderBlue->y() + height()) / 2);
    painter->setPen(Qt::darkMagenta);
    for (int i = 0; i < player->msg.sample_size; ++i) {
        qpoints[i] = QPoint(i * ui->sliderBlue->width() / player->msg.sample_size,
                            -(int) (player->msg.fft[i] * (float) i * 20 * player->rgb_parameters.sensitivity));
    }
    float rpeak = player->rgb_parameters.red_peak;
    float gpeak = player->rgb_parameters.green_peak;
    float bpeak = player->rgb_parameters.blue_peak;
    float width = player->rgb_parameters.width;
    float smpls = (float) player->msg.sample_size / 2;
//    float snstv = -player->rgb_parameters.sensitivity * 2500;

    painter->drawPolyline(qpoints, player->msg.sample_size);
    painter->setPen(Qt::darkRed);
    painter->drawLine(std::max((int) ((float) ui->sliderBlue->width() * (rpeak - width / 2) / smpls), 0), 0,
                      (int) ((float) ui->sliderBlue->width() * rpeak / smpls), (int)(-100 * player->rgb_parameters.red_imp));
    painter->drawLine(std::min((int) ((float) ui->sliderBlue->width() * (rpeak + width / 2) / smpls),
                               ui->sliderBlue->width()), 0,
                      (int) ((float) ui->sliderBlue->width() * rpeak / smpls), (int)(-100 * player->rgb_parameters.red_imp));

    painter->setPen(Qt::darkGreen);
    painter->drawLine(std::max((int) ((float) ui->sliderBlue->width() * (gpeak - width / 2) / smpls), 0), 0,
                      (int) ((float) ui->sliderBlue->width() * gpeak / smpls), (int)(-100 * player->rgb_parameters.green_imp));
    painter->drawLine(std::min((int) ((float) ui->sliderBlue->width() * (gpeak + width / 2) / smpls),
                               ui->sliderBlue->width()), 0,
                      (int) ((float) ui->sliderBlue->width() * gpeak / smpls), (int)(-100 * player->rgb_parameters.green_imp));

    painter->setPen(Qt::darkBlue);
    painter->drawLine(std::max((int) ((float) ui->sliderBlue->width() * (bpeak - width / 2) / smpls), 0), 0,
                      (int) ((float) ui->sliderBlue->width() * bpeak / smpls), (int)(-100 * player->rgb_parameters.blue_imp));
    painter->drawLine(std::min((int) ((float) ui->sliderBlue->width() * (bpeak + width / 2) / smpls),
                               ui->sliderBlue->width()), 0,
                      (int) ((float) ui->sliderBlue->width() * bpeak / smpls), (int)(-100 * player->rgb_parameters.blue_imp));

    painter->restore();
    delete painter;
}

void Color::on_buttonReset_clicked() {
    player->rgb_parameters.tweak(RGBParameters());
    ui->sliderBlue->setSliderPosition(player->rgb_parameters.blue_peak);
    ui->sliderGreen->setSliderPosition(player->rgb_parameters.green_peak);
    ui->sliderRed->setSliderPosition(player->rgb_parameters.red_peak);
    ui->sliderWidth->setSliderPosition(player->rgb_parameters.width);
    ui->checkMinFilter->setCheckState(Qt::Checked);
    ui->nobSensitivity->setSliderPosition(0);
    ui->nobFilter->setSliderPosition(0);
    ui->nobBPM->setSliderPosition(player->rgb_parameters.bpm);
}

void Color::on_nobBPM_valueChanged(int value) {
    player->rgb_parameters.bpm = value;
    ui->editBPM->setPlainText(QString(std::to_string(player->rgb_parameters.bpm).c_str()));
}

void Color::on_editBPM_textChanged() {
    int tmp = (int) strtol(ui->editBPM->toPlainText().toUtf8().data(),
                           (char **) (ui->editBPM->toPlainText().toUtf8().data()
                               + ui->editBPM->toPlainText().toUtf8().length()), 10);
    if (tmp >= 30) {
        player->rgb_parameters.bpm = tmp;
    }
    ui->nobBPM->setSliderPosition(tmp);
}

void Color::on_nobImpactR_valueChanged(int value) {
    player->rgb_parameters.red_imp = (float_t)value / 400;
}

void Color::on_nobImpactG_valueChanged(int value) {
    player->rgb_parameters.green_imp = (float_t)value / 400;
}

void Color::on_nobImpactB_valueChanged(int value) {
    player->rgb_parameters.blue_imp = (float_t)value / 400;
}
