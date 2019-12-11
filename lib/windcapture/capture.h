#ifndef WINDCAPTURE_H
#define WINDCAPTURE_H

#include <windows.h>

class WindCapture
{
public:
    WindCapture();
    ~WindCapture();
    void get_sample(float *pDouble, int32_t i);
    void set_device(char *sound_device_name);

    bool isSet;
};

#endif // WINDCAPTURE_H
