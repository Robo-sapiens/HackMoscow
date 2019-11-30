//
// Created by kira on 26.11.2019.
//

#include <iostream>
#include "msg.h"


Msg::Msg(size_t size) :
    sample_size(size),
    fft((float *) calloc(sample_size, sizeof(float))),
    text(),
    is_settings() {
    set_default();
}

Msg::~Msg() {
    free(fft);
}

int32_t Msg::actual_size() const{
    return sample_size / 2;
}

void Msg::set_default() {
    is_settings = false;
    text = "{0000}<000000000>";
}

void Msg::set_settings(int32_t mode, int32_t verteces, const float *x, const float *y, int32_t bpm, float_t rotation) {
    is_settings = true;
    int32_t sum = 0;
    text =  "{0000}[";
    text += std::to_string(verteces);
    text += std::to_string(mode);
    sum += verteces;
    sum += mode;
    for (int32_t kI = 0; kI < verteces; ++kI) {
        std::string tmp("000000");
        int32_t x_tmp = (int32_t)((x[kI] + 20) * 10) % 1000;
        tmp[0]  = '0' + (x_tmp / 100);
        tmp[1]  = '0' + (x_tmp / 10 % 10);
        tmp[2]  = '0' + (x_tmp % 10);
        int32_t y_tmp = (int32_t)((y[kI] + 20) * 10) % 1000;
        tmp[3]  = '0' + (y_tmp / 100);
        tmp[4]  = '0' + (y_tmp / 10 % 10);
        tmp[5]  = '0' + (y_tmp % 10);
        text += tmp;
        sum += x_tmp;
        sum += y_tmp;
    }
    std::string tmp("000000");
    tmp[0]  = '0' + (bpm / 100);
    tmp[1]  = '0' + (bpm / 10 % 10);
    tmp[2]  = '0' + (bpm % 10);
    auto rot_tmp = (int32_t)((rotation * M_1_PI * 180) + 20);
    tmp[3]  = '0' + (rot_tmp / 100);
    tmp[4]  = '0' + (rot_tmp / 10 % 10);
    tmp[5]  = '0' + (rot_tmp % 10);
    text += tmp;
    text += ']';
    sum += bpm + rot_tmp;
    text[1] = '2' + (sum / 1000);
    text[2] = '0' + (sum / 100 % 10);
    text[3] = '0' + (sum / 10 % 10);
    text[4] = '0' + (sum % 10);
}

void Msg::set_new_led(int32_t width, int32_t length) {
    is_settings = true;
    text = "{1000}[0000]";
    text[2] = '0' + ((width + length) / 100);
    text[3] = '0' + ((width + length) / 10 % 10);
    text[4] = '0' + ((width + length) % 10);

    text[7] = width / 10;
    text[8] = width % 10;
    text[9] = length / 10;
    text[10] = length % 10;
}
