//
// Created by kira on 16.11.2019.
//

#include "audio_thread.h"
#include <QDebug>


AudioThread::AudioThread(Player *player)
    : player(player) {}

void AudioThread::run() {
    auto in = (float *) calloc(player->msg.sample_size, sizeof(float));
    while (player->capture_device.isSet) {
        player->capture_device.get_sample(in, player->msg.sample_size);
        BASS_StreamPutData(player->hstream, in, player->msg.sample_size);
        if (BASS_ChannelGetData(player->hstream, player->msg.fft, BASS_DATA_FFT1024) == -1) {
            break;
        }
    }
    free(in);
    player->error_handler();
}

