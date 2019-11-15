//
// Created by kira on 10.11.2019.
//

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdint>
#include <iostream>

#include "capture.h"
#include "list_devices.h"

#define POSSIBLE_AMOUNT_OF_DEVICES 32

pa::Capture::Capture() {
    auto pa_input_devicelist =  (pa_devicelist_t *)calloc(POSSIBLE_AMOUNT_OF_DEVICES, sizeof(pa_devicelist_t));
    auto pa_output_devicelist = (pa_devicelist_t *)calloc(POSSIBLE_AMOUNT_OF_DEVICES, sizeof(pa_devicelist_t));

    if (pa_get_devicelist(pa_input_devicelist, pa_output_devicelist) < 0) {
        return;
    }
    int32_t device = 0;
    std::string device_name = pa_input_devicelist[device].name;
#ifndef WITH_GUI
    for (int32_t i = 0; i < POSSIBLE_AMOUNT_OF_DEVICES; i++) {
        if (!pa_output_devicelist[i].initialized) {
            break;
        }
        std::cout << "=======[ Output Device #" << i <<  "]=======" << std::endl;
        std::cout << "Description: " << pa_output_devicelist[i].description << std::endl;
        std::cout << "Name: " << pa_output_devicelist[i].name << std::endl;
        std::cout << "Index: " << pa_output_devicelist[i].index << std::endl << std::endl;
    }
    for (int32_t i = 0; i < POSSIBLE_AMOUNT_OF_DEVICES; i++) {
        if (!pa_input_devicelist[i].initialized) {
            break;
        }
        std::cout << "=======[ Input Device #" << i <<  "]=======" << std::endl;
        std::cout << "Description: " << pa_input_devicelist[i].description << std::endl;
        std::cout << "Name: " << pa_input_devicelist[i].name << std::endl;
        std::cout << "Index: " << pa_input_devicelist[i].index << std::endl << std::endl;
    }

    std::cout << "wogui" << std::endl;
    bool yes = false;
    std::cout << "input ?" << std::endl;
    std::cin >> yes;
    std::cout << "number of device" << std::endl;
    std::cin >> device;
    if (yes) {
        device_name = pa_input_devicelist[device].name;
    } else {
        device_name = pa_output_devicelist[device].name;
    }
#endif // WITH_GUI
    int32_t error = 0;
    simple = pa_simple_new(NULL, "player_usage", PA_STREAM_RECORD,
                  device_name.c_str(),"record", &ss, NULL, NULL, &error);
    if (!simple) {
        std::cout << pa_strerror(error) << std::endl;
    }
}

pa::Capture::~Capture() {
    pa_simple_free(simple);
}

uint32_t pa::Capture::get_sample(void *buf, size_t sample_size) {
    int32_t error = 0;
    uint32_t pa_read = pa_simple_read(simple, buf, sample_size * sizeof(float), &error);

    if (pa_read < 0) {
        std::cout << pa_strerror(error) << std::endl;
    }

    return pa_read;
}
