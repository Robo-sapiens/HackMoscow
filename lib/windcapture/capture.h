#ifndef WINDCAPTURE_H
#define WINDCAPTURE_H

#include <string>
#include <vector>
#include <QString>
#include <cmath>
#include <basswasapi/c/basswasapi.h>

class WindCapture
{
public:
    WindCapture();
    void get_device_list(QStringList & other_device_list);
    void get_sample(float_t *fdata);
    void set_device(int32_t i);

    bool isSet;
    std::vector<std::pair<int, QString>> device_list;
};

#endif // WINDCAPTURE_H
