#include <QApplication>
#include <QString>
#include "main_window.h"
#include "player.h"
#include "serial_thread.h"
#include "audio_thread.h"
#include "fft_thread.h"
#include "animation.h"
#include "color.h"
#include "devices.h"
#include "animationpresettings.h"

#define DELAY 5000

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Player player(DELAY);

    AnimationPreSettings animation_pre_settings(nullptr, &player);
    Color color(nullptr, &player);
    Devices devices(nullptr, &player);
    SerialThread serial_thread(&player);
    AudioThread audio_thread(&player);
    FFTWThread fftw_thread(&player);
    MainWindow main_window(nullptr, &player);

    color.setWindowModality(Qt::NonModal);

    QObject::connect(&main_window, SIGNAL(open_colors()), &color, SLOT(showMaximized()));
    QObject::connect(&main_window, SIGNAL(open_animation()), &animation_pre_settings, SLOT(show()));
    QObject::connect(&main_window, SIGNAL(open_devices()), &devices, SLOT(showMaximized()));
    QObject::connect(&devices, SIGNAL(start_capture()), &audio_thread, SLOT(start()));
    QObject::connect(&devices, SIGNAL(start_capture()), &fftw_thread, SLOT(start()));
    QObject::connect(&devices, SIGNAL(start_port(const QSerialPortInfo &)),
                     &serial_thread, SLOT(start_port(const QSerialPortInfo &)));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), &color, SLOT(update()));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), &main_window, SLOT(update()));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), &animation_pre_settings.animation_, SLOT(update()));
    QObject::connect(&animation_pre_settings.animation_, SIGNAL(change_verteces(int,
                                            const fPoint *, float, int)),
                     &main_window, SLOT(animation_changed(int,
                                            const fPoint *, float, int)));
    QObject::connect(&animation_pre_settings.animation_, SIGNAL(change_rotation(float)),
                     &main_window, SLOT(rotation_changed(float)));

    main_window.showMaximized();

    return QApplication::exec();
}
