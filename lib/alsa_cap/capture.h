//
// Created by kira on 12.11.2019.
//

#ifndef PLAYER_CAPTURE_H
#define PLAYER_CAPTURE_H

#include <alsa/asoundlib.h>
#include <cstdint>

namespace alsa {
    class Capture {
    public:
        Capture();
        ~Capture();
        uint32_t get_sample(void *buf, size_t sample_size);
    private:
        snd_pcm_t *capture_handle;
        int32_t err;
    };
}
#endif //PLAYER_CAPTURE_H
