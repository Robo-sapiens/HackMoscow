//
// Created by kira on 22.11.2019.
//

#ifndef PLAYER_UI_RGBPARAMETERS_H
#define PLAYER_UI_RGBPARAMETERS_H

#include <cstdint>
#include <cmath>


#define SAMPLE_SIZE 512  // connected to BASS_FFT_1024


class RGBParameters {
public:
    RGBParameters();
    void tweak(RGBParameters rgb_params);
    int32_t width;
    int32_t red_peak;
    int32_t green_peak;
    int32_t blue_peak;
    int32_t bpm;
    float_t red_imp;
    float_t green_imp;
    float_t blue_imp;
    float_t filter;
    float_t sensitivity;
    bool tweak_by_min;
};


#endif //PLAYER_UI_RGBPARAMETERS_H
