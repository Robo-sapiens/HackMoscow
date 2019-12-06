#include "presets.h"
#include "ui_presets.h"
#include <QDebug>
#include <sstream>
#include <QDir>


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
    QString params = get_param_string();
    QFile presets_file("presets/" + filename + identifier());
    qDebug() << presets_file.open(QIODevice::WriteOnly);
    presets_file.write(params.toUtf8());
    parse_files();
    presets_file.close();
}

void Presets::parse_files() {
    QString path("presets/");
    QDir presets_dir(path);
    if (!presets_dir.exists()) {
        presets_dir.mkpath(presets_dir.absolutePath());
    }
    QStringList filter;
    filter << "*" + identifier();
    presets_dir.setNameFilters(filter);
    ui->listCfgs->clear();
    ui->listCfgs->addItems(presets_dir.entryList());
}

void Presets::showEvent(QShowEvent *event) {
    parse_files();
    QWidget::showEvent(event);
}

void ColorsPresets::set_params(RGBParameters *params) {
    this->_params = params;
}

void ColorsPresets::on_buttonApply_clicked() {
    QStringList param_list;
    QString filename = ui->listCfgs->currentItem()->text();
    QFile presets_file("presets/" + filename);
    presets_file.open(QIODevice::ReadOnly);
    _params->width = QString(presets_file.readLine()).toInt();
    _params->red_peak = QString(presets_file.readLine()).toInt();
    _params->green_peak = QString(presets_file.readLine()).toInt();
    _params->blue_peak = QString(presets_file.readLine()).toInt();
    _params->bpm = QString(presets_file.readLine()).toInt();
    _params->red_imp = QString(presets_file.readLine()).toInt();
    _params->green_imp = QString(presets_file.readLine()).toInt();
    _params->blue_imp = QString(presets_file.readLine()).toInt();
    _params->filter = QString(presets_file.readLine()).toInt();
    _params->sensitivity = QString(presets_file.readLine()).toFloat();
    _params->tweak_by_min = QString(presets_file.readLine()).toInt();
    emit new_setting();
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
    _params = params;
}

void AnimationPresets::on_buttonApply_clicked() {

}

QString AnimationPresets::identifier() const {
    return ".anicfg";
}

QString AnimationPresets::get_param_string() {
    std::stringstream stream;
    stream << _params->vectors->size() << std::endl;
    for (auto &real_vector: *_params->real_vectors) {
        stream << real_vector.x << std::endl;
        stream << real_vector.y << std::endl;
    }
    stream << _params->radius << std::endl
           << _params->mode << std::endl
           << _params->rotation << std::endl;
    return QString(stream.str().c_str());
}
