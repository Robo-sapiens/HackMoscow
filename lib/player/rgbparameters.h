//
// Created by kira on 22.11.2019.
//

#ifndef PLAYER_UI_RGBPARAMETERS_H
#define PLAYER_UI_RGBPARAMETERS_H

#include <cstdint>
#include <cmath>

class RGBParameters
{
public:
    RGBParameters(
            int32_t  width,
            int32_t  filter,
            int32_t  red_peak,
            int32_t  green_peak,
            int32_t  blue_peak,
            double_t sensitivity,
            int32_t  bpm,
            bool     tweak_by_min);
    void tweak(RGBParameters rgb_params);
    int32_t  width;
    int32_t  filter;
    int32_t  red_peak;
    int32_t  green_peak;
    int32_t  blue_peak;
    double_t sensitivity;
    int32_t  bpm;
    bool     tweak_by_min;
};

#endif //PLAYER_UI_RGBPARAMETERS_H
