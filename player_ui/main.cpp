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
#include "polygon.h"

#define DELAY 5000

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Player player(DELAY);

    Animation animation(nullptr, &player);
    Color color(nullptr, &player);
    Devices devices(nullptr, &player);
    SerialThread serial_thread(&player);
    AudioThread audio_thread(&player);
    FFTWThread fftw_thread(&player);
    MainWindow main_window(nullptr, &player);

    QObject::connect(&main_window, SIGNAL(open_colors()), &color, SLOT(showMaximized()));
    QObject::connect(&main_window, SIGNAL(open_animation()), &animation, SLOT(showMaximized()));
    QObject::connect(&main_window, SIGNAL(open_devices()), &devices, SLOT(showMaximized()));
    QObject::connect(&devices, SIGNAL(start_capture()), &audio_thread, SLOT(start()));
    QObject::connect(&devices, SIGNAL(start_capture()), &fftw_thread, SLOT(start()));
    QObject::connect(&devices, SIGNAL(start_port(
                                          const QSerialPortInfo &)),
                     &serial_thread, SLOT(start_port(
                                              const QSerialPortInfo &)));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), &color, SLOT(update()));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), &main_window, SLOT(update()));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), &animation, SLOT(update()));

    main_window.showMaximized();
//    main_window.showFullScreen(); //TODO
    return QApplication::exec();
}
