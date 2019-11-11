//
// Created by kira on 10.11.2019.
//

#include <fftw3.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <cmath>
#include <iostream>
#include <mutex>

#include "fourier_processing.h"


// definitely changeable
#define WIDTH 128
//#define FILTER 0.001 // [0..step = 0.001..0.05]
#define SLOPE 0  // [0..WIDTH]
#define RPEAK 0
#define GPEAK (BUFSIZE / 4)
#define BPEAK (BUFSIZE / 2)

std::mutex g_lock;

enum {re, im}; //real and imaginary

void parseFFT(msg_buf & Msg_buf) {
    while (true) {
        double r = 0, g = 0, b = 0;
        for (int i = std::max(0, RPEAK - WIDTH + SLOPE); i < std::min(512, RPEAK + WIDTH - SLOPE); ++i) {
            r +=
//                    (Msg_buf.fft[i] > FILTER ? Msg_buf.fft[i] : 0) *
                    Msg_buf.fft[i] * (double)std::abs(WIDTH - SLOPE - (RPEAK - i)) / (WIDTH - SLOPE);
        }
        for (int i = std::max(0, GPEAK - WIDTH + SLOPE); i < std::min(512, GPEAK + WIDTH - SLOPE); ++i) {
            g +=
//                    (Msg_buf.fft[i] > FILTER ? Msg_buf.fft[i] : 0) *
                    Msg_buf.fft[i] *
                    (double)std::abs(WIDTH - SLOPE - (GPEAK - i)) / (WIDTH - SLOPE);
        }
        for (int i = std::max(0, BPEAK - WIDTH + SLOPE); i < std::min(512, BPEAK + WIDTH - SLOPE); ++i) {
            b +=
//                    (Msg_buf.fft[i] > FILTER ? Msg_buf.fft[i] : 0) *
                    Msg_buf.fft[i] *
                    (double)std::abs(WIDTH - SLOPE - (BPEAK - i)) / (WIDTH - SLOPE);
        }

//
//        std::cout << r << ' ' << g << ' ' << b << std::endl;
        g_lock.lock();
        Msg_buf.msg[1] = '0' + (char)((int)r / 100);
        Msg_buf.msg[2] = '0' + (char)((int)r / 10 % 10);
        Msg_buf.msg[3] = '0' + (char)((int)r % 10);
        Msg_buf.msg[4] = '0' + (char)((int)g / 100);
        Msg_buf.msg[5] = '0' + (char)((int)g / 10 % 10);
        Msg_buf.msg[6] = '0' + (char)((int)g % 10);
        Msg_buf.msg[7] = '0' + (char)((int)b / 100);
        Msg_buf.msg[8] = '0' + (char)((int)b / 10 % 10);
        Msg_buf.msg[9] = '0' + (char)((int)b % 10);
        g_lock.unlock();
    }
}

void getFFT(msg_buf &Msg_buf) {
    auto buf = (SAMPLE_TYPE *)malloc(sizeof(SAMPLE_TYPE) * BUFSIZE);
    auto in  = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * BUFSIZE);
    auto out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * BUFSIZE);
    fftw_plan p = fftw_plan_dft_1d(BUFSIZE, in, out, FFTW_FORWARD, FFTW_MEASURE);
    float max = 0;
    float min = 0;
    while (true) {
        int error = 0;
        if (pa_simple_read(Msg_buf.s, buf, BUFSIZE * sizeof(SAMPLE_TYPE), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            break;
        }

        for (int i = 0; i < BUFSIZE; ++i) {
            min = std::min(min, buf[i]);
            max = std::max(max, buf[i]);
            in[i][re] = (double)buf[i];
            in[i][im] = 0.0;
        }
        fftw_execute(p);

        for (int j = 0; j < BUFSIZE / 2; ++j) {
            Msg_buf.fft[j] = std::sqrt(out[j][re] * out[j][re] + out[j][im] * out[j][im]);
        }
        std::cout << min << ' ' << max << std::endl;

    }
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
    free(buf);
}
