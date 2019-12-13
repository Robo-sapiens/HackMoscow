QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/lib
INCLUDEPATH += $$PWD/lib/player
INCLUDEPATH += $$PWD/lib/windcapture
INCLUDEPATH += $$PWD/player_ui/animation
INCLUDEPATH += $$PWD/player_ui/color
INCLUDEPATH += $$PWD/player_ui/devices
INCLUDEPATH += $$PWD/player_ui/main_window
INCLUDEPATH += $$PWD/player_ui/presets
INCLUDEPATH += $$PWD/player_ui/polygon
INCLUDEPATH += $$PWD/player_ui/thread_workers


SOURCES += \
    lib/windcapture/capture.cpp \
    lib/player/player.cpp \
    lib/player/rgbparameters.cpp \
    lib/player/msg.cpp \
    src/main.cpp \
    player_ui/animation/animation.cpp \
    player_ui/animation/animation_view.cpp \
    player_ui/animation/animationpresettings.cpp \
    player_ui/color/color.cpp \
    player_ui/devices/devices.cpp \
    player_ui/main_window/tabbable_main_window.cpp \
    player_ui/polygon/polygon.cpp \
    player_ui/presets/presets.cpp \
    player_ui/presets/savenewdial.cpp \
    player_ui/thread_workers/audio_thread.cpp \
    player_ui/thread_workers/fft_thread.cpp \
    player_ui/thread_workers/serial_thread.cpp \


HEADERS += \
    lib/windcapture/capture.h \
    lib/player/player.h \
    lib/player/rgbparameters.h \
    lib/player/msg.h \
    lib/bass.h \
    lib/fixed_queue.h \
    player_ui/animation/animation.h \
    player_ui/animation/animation_view.h \
    player_ui/animation/animationpresettings.h \
    player_ui/color/color.h \
    player_ui/devices/devices.h \
    player_ui/main_window/tabbable_main_window.h \
    player_ui/polygon/polygon.h \
    player_ui/presets/presets.h \
    player_ui/presets/savenewdial.h \
    player_ui/thread_workers/audio_thread.h \
    player_ui/thread_workers/fft_thread.h \
    player_ui/thread_workers/serial_thread.h \

FORMS += \
    player_ui/animation/animation.ui \
    player_ui/animation/animation_view.ui \
    player_ui/animation/animationpresettings.ui \
    player_ui/color/color.ui \
    player_ui/devices/devices.ui \
    player_ui/main_window/tabbable_main_window.ui \
    player_ui/presets/presets.ui \
    player_ui/presets/savenewdial.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/bass/c/x64/ -lbass
win32: LIBS += -L$$PWD/bass/x64/ -lbass

INCLUDEPATH += $$PWD/bass/c/x64
DEPENDPATH += $$PWD/bass/c/x64
INCLUDEPATH += $$PWD/bass/x64
DEPENDPATH += $$PWD/bass/x64
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

LIBS += -lole32 -loleaut32

win32: LIBS += -L$$PWD/basswasapi/c/x64/ -lbasswasapi
win32: LIBS += -L$$PWD/basswasapi/x64/ -lbasswasapi

INCLUDEPATH += $$PWD/basswasapi/c/x64
DEPENDPATH += $$PWD/basswasapi/c/x64
INCLUDEPATH += $$PWD/basswasapi/x64
DEPENDPATH += $$PWD/basswasapi/x64
