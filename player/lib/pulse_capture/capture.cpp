//
// Created by kira on 10.11.2019.
//

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdint>
#include <iostream>

#include "capture.h"


pa::Capture::Capture() {
    int32_t error = 0;
    simple = pa_simple_new(NULL, "player_usage", PA_STREAM_RECORD,
                  "alsa_output.pci-0000_00_1b.0.analog-stereo.monitor", // TODO
                  "record", &ss, NULL, NULL, &error);

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
