//
// Created by kira on 12.11.2019.
//

#ifndef PLAYER_CAPTURE_H
#define PLAYER_CAPTURE_H

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdint>

namespace pa {
    class Capture {
    public:
        Capture();
        ~Capture();
        uint32_t get_sample(void *buf, size_t sample_size);
    private:
        const pa_sample_spec ss = {
                .format = PA_SAMPLE_FLOAT32,
                .rate = 44100,
                .channels = 1
        };
        pa_simple *simple;
    };
}
#endif //PLAYER_CAPTURE_H
