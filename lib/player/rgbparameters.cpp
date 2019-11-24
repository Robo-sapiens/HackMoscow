//
// Created by kira on 22.11.2019.
//

#include "rgbparameters.h"


RGBParameters::RGBParameters()
    : width(SAMPLE_SIZE / 4), filter(0), red_peak(0), green_peak(255),
      blue_peak(127), sensitivity(255. / 5000), bpm(100), tweak_by_min(true),
      red_imp(1), green_imp(1), blue_imp(1) {}

void RGBParameters::tweak(RGBParameters rgb_params) {
    *this = rgb_params;
}
