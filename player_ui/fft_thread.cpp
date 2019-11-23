//
// Created by kira on 17.11.2019.
//

#include "fft_thread.h"
#include <QDebug>


FFTWThread::FFTWThread(Player *player) : player(player), qMutex(new QMutex()) {}


void FFTWThread::run() {
    while (!player->error_code) {
        int32_t r = 0, g = 0, b = 0;
        for (int32_t i = std::max(0, player->rgb_parameters.red_peak - player->rgb_parameters.width);
             i < std::min(player->msg.sample_size, player->rgb_parameters.red_peak + player->rgb_parameters.width); ++i) {
            if (player->msg.fft[i] > player->rgb_parameters.filter) {
                r += player->msg.fft[i] * std::abs(player->rgb_parameters.width - (player->rgb_parameters.red_peak - (float) i)) / (player->rgb_parameters.width) * i;
            }
        }
        for (int32_t i = std::max(0, player->rgb_parameters.green_peak - player->rgb_parameters.width);
             i < std::min(player->msg.sample_size, player->rgb_parameters.green_peak + player->rgb_parameters.width); ++i) {
            if (player->msg.fft[i] > player->rgb_parameters.filter) {
                g += player->msg.fft[i] * std::abs(player->rgb_parameters.width - (player->rgb_parameters.green_peak - (float) i)) / (player->rgb_parameters.width) * i;
            }
        }
        for (int32_t i = std::max(0, player->rgb_parameters.blue_peak - player->rgb_parameters.width);
             i < std::min(player->msg.sample_size, player->rgb_parameters.blue_peak + player->rgb_parameters.width); ++i) {
            if (player->msg.fft[i] > player->rgb_parameters.filter) {
                b += player->msg.fft[i] * std::abs(player->rgb_parameters.width - (player->rgb_parameters.blue_peak - (float) i)) / (player->rgb_parameters.width) * i;
            }
        }
        if (player->rgb_parameters.tweak_by_min) {
            int32_t min_val = std::min(r, std::min(g, b));
            r -= min_val;
            g -= min_val;
            b -= min_val;
        }
        r *= player->rgb_parameters.sensitivity;
        g *= player->rgb_parameters.sensitivity;
        b *= player->rgb_parameters.sensitivity;
        if (r > 255) {
            r = 255;
        }
        if (g > 255) {
            g = 255;
        }
        if (b > 255) {
            b = 255;
        }

//        qDebug() << r << g << b;
        qMutex->lock();

        player->rgb.r = r;
        player->rgb.g = g;
        player->rgb.b = b;
        player->msg.text[1] = '0' + (char) ((int32_t) r / 100);
        player->msg.text[2] = '0' + (char) ((int32_t) r / 10 % 10);
        player->msg.text[3] = '0' + (char) ((int32_t) r % 10);
        player->msg.text[4] = '0' + (char) ((int32_t) g / 100);
        player->msg.text[5] = '0' + (char) ((int32_t) g / 10 % 10);
        player->msg.text[6] = '0' + (char) ((int32_t) g % 10);
        player->msg.text[7] = '0' + (char) ((int32_t) b / 100);
        player->msg.text[8] = '0' + (char) ((int32_t) b / 10 % 10);
        player->msg.text[9] = '0' + (char) ((int32_t) b % 10);

        qMutex->unlock();
        emit new_data();
    }
}


FFTWThread::~FFTWThread() {
    delete qMutex;
}
