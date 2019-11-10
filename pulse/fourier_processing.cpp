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

#define BUFSIZE 1024

// definitely changeable
#define MIN_VAL 10
#define WIDTH 128
#define GAIN 1.15
//#define FILTER 0.001 // [0..step = 0.001..0.05]
#define SLOPE 0  // [0..400]
#define RPEAK 0    // [0..1024]
#define GPEAK 512  // [0..1024]
#define BPEAK 256  // [0..1024]

std::mutex g_lock;


void parseFFT(msg_buf & Msg_buf) {
    Msg_buf.fft = new float[BUFSIZE];
    while (true) {
        float r = 0, g = 0, b = 0;
        for (int i = std::max(0, RPEAK - WIDTH + SLOPE); i < std::min(512, RPEAK + WIDTH - SLOPE); ++i) {
            r +=
//                    (Msg_buf.fft[i] > FILTER ? Msg_buf.fft[i] : 0) *
                    (float)std::abs(WIDTH - SLOPE - (RPEAK - i)) / (WIDTH - SLOPE) *
                    (float)pow(2, (int)(RPEAK / 256));
        }
        for (int i = std::max(0, GPEAK - WIDTH + SLOPE); i < std::min(512, GPEAK + WIDTH - SLOPE); ++i) {
            g +=
//                    (Msg_buf.fft[i] > FILTER ? Msg_buf.fft[i] : 0) *
                    (float)std::abs(WIDTH - SLOPE - (GPEAK - i)) / (WIDTH - SLOPE) *
                    (float)pow(2, (int)(GPEAK / 256));
        }
        for (int i = std::max(0, BPEAK - WIDTH + SLOPE); i < std::min(512, BPEAK + WIDTH - SLOPE); ++i) {
            b +=
//                    (Msg_buf.fft[i] > FILTER ? Msg_buf.fft[i] : 0) *
                    (float)std::abs(WIDTH - SLOPE - (BPEAK - i)) / (WIDTH - SLOPE) *
                    (float)pow(2, (int)(BPEAK / 256));
        }

//        if (r > 2) {
//            r = std::pow(2, r - 1);
//        }
//        if (g > 2) {
//            g = std::pow(2, g - 1);
//        }
//        if (b > 2) {
//            b = std::pow(2, b - 1);
//        }
//        if (r > 255) {
//            r = 255;
//        }
//        if (g > 255) {
//            g = 255;
//        }
//        if (b > 255) {
//            b = 255;
//        }
//        if (r < MIN_VAL && g < MIN_VAL && b < MIN_VAL) {
//            r = std::pow(r, GAIN);
//            g = std::pow(g, GAIN);
//            b = std::pow(b, GAIN);
//        }

//        std::cout << r << ' ' << g << ' ' << b << std::endl;
        g_lock.lock();
//        Msg_buf.msg[1] = '0' + (char)((int)r / 100);
//        Msg_buf.msg[2] = '0' + (char)((int)r / 10 % 10);
//        Msg_buf.msg[3] = '0' + (char)((int)r % 10);
//        Msg_buf.msg[4] = '0' + (char)((int)g / 100);
//        Msg_buf.msg[5] = '0' + (char)((int)g / 10 % 10);
//        Msg_buf.msg[6] = '0' + (char)((int)g % 10);
//        Msg_buf.msg[7] = '0' + (char)((int)b / 100);
//        Msg_buf.msg[8] = '0' + (char)((int)b / 10 % 10);
//        Msg_buf.msg[9] = '0' + (char)((int)b % 10);
        g_lock.unlock();
    }
    delete[] Msg_buf.fft;
}

void getFFT(struct msg_buf &Msg_buf) {
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * BUFSIZE);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * BUFSIZE);
    while (true) {
        auto buf = new float[BUFSIZE];
        int error;
        if (pa_simple_read(Msg_buf.s, buf, sizeof(buf), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            break;
        }

        float max = 0;
        float min = 0;
        for(int i = 0; i < BUFSIZE; ++i) {
            min = std::min(buf[i], min);
            max = std::max(buf[i], max);
            in[i][re] = buf[i];
            in[i][im] = 0.0;
        }
        std::cout << min << ' ' << max << std::endl;
        delete[] buf;
        p = fftw_plan_dft_1d(BUFSIZE, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p);
        fftw_destroy_plan(p);

        for(int j = 0; j < 1024; j += 2) {
            double real = out[j][re];
            double imag = out[j][im];
            Msg_buf.fft[j] = real / 32000;
        }
    }
    fftw_free(in);
    fftw_free(out);
}