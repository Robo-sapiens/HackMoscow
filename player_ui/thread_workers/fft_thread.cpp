//
// Created by kira on 17.11.2019.
//

#include "fft_thread.h"
#include <QDebug>
#include <algorithm>
using std::max;
using std::min;
using std::abs;

FFTWThread::FFTWThread(Player *player) : player(player), qMutex(new QMutex()) {}

void FFTWThread::run() {
    while (!player->error_code) {
        int32_t r = 0, g = 0, b = 0;
        for (int32_t i = max(0, player->rgb_parameters.red_peak - player->rgb_parameters.width);
             i < min(player->msg.actual_size(), player->rgb_parameters.red_peak + player->rgb_parameters.width);
             ++i) {
            if (player->msg.fft[i] > player->rgb_parameters.filter) {
                r += player->msg.fft[i]
                    * abs(player->rgb_parameters.width - (player->rgb_parameters.red_peak - (float) i))
                    * i
                    / (player->rgb_parameters.width);
            }
        }
        for (int32_t i = max(0, player->rgb_parameters.green_peak - player->rgb_parameters.width);
             i < min(player->msg.actual_size(), player->rgb_parameters.green_peak + player->rgb_parameters.width);
             ++i) {
            if (player->msg.fft[i] > player->rgb_parameters.filter) {
                g += player->msg.fft[i]
                    * abs(player->rgb_parameters.width - (player->rgb_parameters.green_peak - (float) i))
                    * i
                    / (player->rgb_parameters.width);
            }
        }
        for (int32_t i = max(0, player->rgb_parameters.blue_peak - player->rgb_parameters.width);
             i < min(player->msg.actual_size(), player->rgb_parameters.blue_peak + player->rgb_parameters.width);
             ++i) {
            if (player->msg.fft[i] > player->rgb_parameters.filter) {
                b += player->msg.fft[i]
                    * abs(player->rgb_parameters.width - (player->rgb_parameters.blue_peak - (float) i))
                    * i
                    / (player->rgb_parameters.width);
            }
        }

        r *= player->rgb_parameters.sensitivity * player->rgb_parameters.red_imp;
        g *= player->rgb_parameters.sensitivity * player->rgb_parameters.green_imp;
        b *= player->rgb_parameters.sensitivity * player->rgb_parameters.blue_imp;

        if (player->rgb_parameters.tweak_by_min) {
            int32_t min_val = min(r, min(g, b));
            r -= min_val;
            g -= min_val;
            b -= min_val;
        }
        r %= 256;
        g %= 256;
        b %= 256;

        qMutex->lock();
        player->rgb.r = r;
        player->rgb.g = g;
        player->rgb.b = b;
        if (!player->msg.is_settings) {
            //TODO: remake somehow
            player->msg.text[2] = '0' + ((r + g + b) / 100);
            player->msg.text[3] = '0' + ((r + g + b) / 10 % 10);
            player->msg.text[4] = '0' + ((r + g + b) % 10);
            player->msg.text[7] = '0' + (r / 100);
            player->msg.text[8] = '0' + (r / 10 % 10);
            player->msg.text[9] = '0' + (r % 10);
            player->msg.text[10] = '0' + (g / 100);
            player->msg.text[11] = '0' + (g / 10 % 10);
            player->msg.text[12] = '0' + (g % 10);
            player->msg.text[13] = '0' + (b / 100);
            player->msg.text[14] = '0' + (b / 10 % 10);
            player->msg.text[15] = '0' + (b % 10);
        }
        qMutex->unlock();

        emit new_data();
    }
}

FFTWThread::~FFTWThread() {
    delete qMutex;
}
