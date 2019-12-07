#ifndef TABBABLE_MAIN_WINDOW_H
#define TABBABLE_MAIN_WINDOW_H

#include <QWidget>
#include "player.h"
#include "color.h"
#include "devices.h"
#include "animationpresettings.h"
#include "serial_thread.h"
#include "audio_thread.h"
#include "fft_thread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TabbableMainWindow; }
QT_END_NAMESPACE

class TabbableMainWindow : public QWidget {
Q_OBJECT

public:
    explicit TabbableMainWindow(QWidget *parent = nullptr);
    ~TabbableMainWindow() override;

private slots:
    void on_previewCheckBox_stateChanged(int arg1);

private:
    Ui::TabbableMainWindow *ui;
    Player player;
    SerialThread serial_thread;
    AudioThread audio_thread;
    FFTWThread fftw_thread;
};


#endif // TABBABLE_MAIN_WINDOW_H
