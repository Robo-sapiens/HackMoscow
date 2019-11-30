#include "presets.h"
#include "ui_presets.h"
#include <QDebug>
#include <sstream>


Presets::Presets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Presets),
    dialog(new SaveNewDial) {
    ui->setupUi(this);
    QObject::connect(ui->buttonSaveNew, SIGNAL(clicked()), dialog, SLOT(show()));
    QObject::connect(dialog, SIGNAL(new_filename(QString)),
                     this, SLOT(dispatch_filename(QString)));
}

Presets::~Presets() {
    delete ui;
    delete dialog;
}

void Presets::dispatch_filename(QString filename) {
//    write_to_file(get_param_string());
    qDebug() << get_param_string();
    qDebug() << filename + identifier();
}

void ColorsPresets::set_params(RGBParameters *params) {
    this->_params = params;
}

void ColorsPresets::on_buttonApply_clicked() {
    qDebug() << "inherited";
}

QString ColorsPresets::identifier() const {
    return ".clrcfg";
}

QString ColorsPresets::get_param_string() {
    std::stringstream stream;
    stream << _params->width << std::endl
           << _params->red_peak << std::endl
           << _params->green_peak << std::endl
           << _params->blue_peak << std::endl
           << _params->bpm << std::endl
           << _params->red_imp << std::endl
           << _params->green_imp << std::endl
           << _params->blue_imp << std::endl
           << _params->filter << std::endl
           << _params->sensitivity << std::endl
           << _params->tweak_by_min << std::endl;
    return QString(stream.str().c_str());
}

void AnimationPresets::set_params(Polygon *params) {

}

void AnimationPresets::on_buttonApply_clicked() {

}

QString AnimationPresets::identifier() const {
    return ".anicfg";
}

QString AnimationPresets::get_param_string() {
    std::stringstream stream;
    stream << _params->verteces << std::endl;
    for (auto &real_vector: *_params->real_vectors) {
        stream << real_vector.x << std::endl;
        stream << real_vector.y << std::endl;
    }
    stream << _params->radius << std::endl
           << _params->mode << std::endl
           << _params->rotation << std::endl;
    return QString(stream.str().c_str());
}
