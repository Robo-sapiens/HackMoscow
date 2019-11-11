//
// Created by kira on 10.11.2019.
//

#ifndef DEMON_FOURIER_PROCESSING_H
#define DEMON_FOURIER_PROCESSING_H


#include <pulse/simple.h>
#include <string>

#define BUFSIZE 1024

typedef float SAMPLE_TYPE;

typedef struct msg_buf {
    msg_buf() : s(nullptr), fft(new double[BUFSIZE / 2]), msg("<000000000>") {};
    ~msg_buf() {delete[] fft;}
    pa_simple * s;
    double * fft;
    std::string msg;
} msg_buf;

void parseFFT(msg_buf & Msg_buf);
void getFFT(msg_buf & Msg_buf);

#endif //DEMON_FOURIER_PROCESSING_H
