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
#define DELAY 10000
#define SAMPLE_SIZE 512  // connected to BASS_FFT_1024

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RGBParameters params = {
            .width = SAMPLE_SIZE / 2,    // [0..SAMPLE_SIZE]
            .filter = 0,                 // [0..idk]
            .red_peak = 0,               // [0..SAMPLE_SIZE] [0..100%]
            .green_peak = 512,           // [0..SAMPLE_SIZE] [0..100%]
            .blue_peak = 256,            // [0..SAMPLE_SIZE] [0..100%]
            .sensitivity = 255. / 5000, // [0..idk]
            .tweak_by_min = false         //
    };
    Player player(DELAY, SAMPLE_SIZE, params);

    Animation animation(nullptr, &player);
    Color color(nullptr, &player);
    Devices devices(nullptr, &player);
    SerialThread serial_thread(&player);
    AudioThread audio_thread(&player);
    FFTWThread fftw_thread(&player);
    MainWindow main_window(nullptr, &player);

    QObject::connect(&main_window, SIGNAL(open_colors()), &color, SLOT(show()));
    QObject::connect(&main_window, SIGNAL(open_animation()), &animation, SLOT(show()));
    QObject::connect(&main_window, SIGNAL(open_devices()), &devices, SLOT(show()));
    QObject::connect(&devices, SIGNAL(start_capture()), &audio_thread, SLOT(start()));
    QObject::connect(&devices, SIGNAL(start_capture()), &fftw_thread, SLOT(start()));
    QObject::connect(&devices, SIGNAL(start_port(const QSerialPortInfo &)), &serial_thread, SLOT(start_port(const QSerialPortInfo &)));

    main_window.show();
    return QApplication::exec();
}
