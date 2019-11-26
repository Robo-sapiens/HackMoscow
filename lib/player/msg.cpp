//
// Created by kira on 26.11.2019.
//

#include "msg.h"


Msg::Msg(size_t size) :
    sample_size(size),
    fft((float *) calloc(sample_size, sizeof(float))),
    text("{0000}<000000000>") {}

Msg::~Msg() {
    free(fft);
}

int32_t Msg::actual_size() const{
    return sample_size / 2;
}
void Msg::set_default() {
    text = "{0000}<000000000>";
}
void Msg::set_settings() {
    text = "{1000}[000000000]";
}
