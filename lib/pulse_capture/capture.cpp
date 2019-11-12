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
        fprintf(stderr, "failed to get device list\n");
        return;
    }

    for (int32_t ctr = 0; ctr < POSSIBLE_AMOUNT_OF_DEVICES; ctr++) {
        if (!pa_output_devicelist[ctr].initialized) {
            break;
        }
        printf("=======[ Output Device #%d ]=======\n", ctr);
        printf("Description: %s\n", pa_output_devicelist[ctr].description);
        printf("Name: %s\n", pa_output_devicelist[ctr].name);
        printf("Index: %d\n", pa_output_devicelist[ctr].index);
        printf("\n");
    }

    for (int32_t ctr = 0; ctr < POSSIBLE_AMOUNT_OF_DEVICES; ctr++) {
        if (!pa_input_devicelist[ctr].initialized) {
            break;
        }
        printf("=======[ Input Device #%d ]=======\n", ctr);
        printf("Description: %s\n", pa_input_devicelist[ctr].description);
        printf("Name: %s\n", pa_input_devicelist[ctr].name);
        printf("Index: %d\n", pa_input_devicelist[ctr].index);
        printf("\n");
    }

    int32_t device = 0;
    bool yes = false;
    std::cout << "input ?" << std::endl;
    std::cin >> yes;
    std::cout << "number of device" << std::endl;
    std::cin >> device;
    std::string device_name;
    if (yes) {
        device_name = pa_input_devicelist[device].name;
    } else {
        device_name = pa_output_devicelist[device].name;
    }

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
        pa_strerror(error);
    }

    return pa_read;
}
