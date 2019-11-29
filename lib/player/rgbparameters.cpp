//
// Created by kira on 22.11.2019.
//

#include "rgbparameters.h"


RGBParameters::RGBParameters() :
    width(SAMPLE_SIZE / 4),
    red_peak(0),
    green_peak(255),
    blue_peak(127),
    red_imp(1),
    bpm(100),
    green_imp(1),
    blue_imp(1),
    filter(0),
    sensitivity(255. / 5000),
    tweak_by_min(true)
    {}

void RGBParameters::tweak(RGBParameters rgb_params) {
    *this = rgb_params;
}
