//
// Created by kira on 17.11.2019.
//

#include "fft_thread.h"
#include <QDebug>


FFTWThread::FFTWThread(Player *player) : player(player), qMutex(new QMutex()) {}


void FFTWThread::run() {
    auto p = player->rgb_parameters;
    while (!player->error_code) {
        int32_t r = 0, g = 0, b = 0;
        for (int32_t i = std::max(0, p.red_peak - p.width);
             i < std::min(player->msg.sample_size, p.red_peak + p.width); ++i) {
            if (player->msg.fft[i] > p.filter) {
                r += player->msg.fft[i] * std::abs(p.width - (p.red_peak - (float) i)) / (p.width) * i;
            }
        }
        for (int32_t i = std::max(0, p.green_peak - p.width);
             i < std::min(player->msg.sample_size, p.green_peak + p.width); ++i) {
            if (player->msg.fft[i] > p.filter) {
                g += player->msg.fft[i] * std::abs(p.width - (p.green_peak - (float) i)) / (p.width) * i;
            }
        }
        for (int32_t i = std::max(0, p.blue_peak - p.width);
             i < std::min(player->msg.sample_size, p.blue_peak + p.width); ++i) {
            if (player->msg.fft[i] > p.filter) {
                b += player->msg.fft[i] * std::abs(p.width - (p.blue_peak - (float) i)) / (p.width) * i;
            }
        }
        if (p.tweak_by_min) {
            int32_t min_val = std::min(r, std::min(g, b));
            r -= min_val;
            g -= min_val;
            b -= min_val;
        }
        r *= p.sensitivity;
        g *= p.sensitivity;
        b *= p.sensitivity;
        if (r > 255) {
            r = 255;
        }
        if (g > 255) {
            g = 255;
        }
        if (b > 255) {
            b = 255;
        }
//        qDebug() << r << g << << b;

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
    }
}


FFTWThread::~FFTWThread() {
    delete qMutex;
}
