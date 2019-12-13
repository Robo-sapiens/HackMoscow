#include "capture.h"
#include <QDebug>

WindCapture::WindCapture() :
    isSet(false) {
    // list of available devices
    BASS_WASAPI_DEVICEINFO info;
    for (DWORD a = 0; BASS_WASAPI_GetDeviceInfo(a, &info); a++) {
        if ((info.flags & BASS_DEVICE_ENABLED) && (info.flags & BASS_DEVICE_LOOPBACK)) {  // and it is enabled
            device_list.push_back({a, info.name});
        }
    }
    if (!(BASS_Init(0, 44100, BASS_DEVICE_LOOPBACK, NULL, NULL))) {
        qDebug() << "puwu common init" << BASS_ErrorGetCode();
    }
}

void WindCapture::get_device_list(QStringList & other_device_list) {
    for (auto & device: device_list) {
        other_device_list << device.second;
    }
}

void WindCapture::get_sample(float_t *fdata) {
    if (isSet) {
        BASS_WASAPI_GetData(fdata, BASS_DATA_FFT1024);
    }
}

void WindCapture::set_device(int32_t i) {
    isSet = false;
    BASS_WASAPI_Stop(true);
    BASS_WASAPI_Free();
    isSet = BASS_WASAPI_Init(device_list[i].first, 0, 0, BASS_WASAPI_BUFFER, 0, 0,
                             [](void *buffer, DWORD length, void *user) {return length;}, NULL);
    if (!isSet) {
        qDebug() << "puwu wasapi init" << BASS_ErrorGetCode();
    }
    isSet = BASS_WASAPI_Start();
    if (!isSet) {
        qDebug() << "puwu wasapi start" << BASS_ErrorGetCode();
    }

}
