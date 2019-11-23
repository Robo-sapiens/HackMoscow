//
// Created by kira on 22.11.2019.
//

#include "rgbparameters.h"

RGBParameters::RGBParameters(int32_t width, int32_t filter, int32_t red_peak, int32_t green_peak, int32_t blue_peak,
                             double_t sensitivity, int32_t bpm, bool tweak_by_min)
                             : width(width), filter(filter), red_peak(red_peak), green_peak(green_peak),
                             blue_peak(blue_peak), sensitivity(sensitivity), bpm(bpm), tweak_by_min(tweak_by_min) {}

void RGBParameters::tweak(RGBParameters rgb_params) {
    *this = rgb_params;
}
