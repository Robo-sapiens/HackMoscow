//
// Created by kira on 16.11.2019.
//

#include "audio_thread.h"
#include <QDebug>


AudioThread::AudioThread(Player *player)
    : player(player) {}

void AudioThread::run() {
    while (player->capture_device.isSet) {
        player->capture_device.get_sample(player->msg.fft);
    }
    player->error_handler();
}

