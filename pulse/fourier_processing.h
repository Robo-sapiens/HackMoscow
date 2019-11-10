//
// Created by kira on 10.11.2019.
//

#ifndef DEMON_FOURIER_PROCESSING_H
#define DEMON_FOURIER_PROCESSING_H

#include "serial_talker.h"

enum {re, im}; //real and imaginary

void parseFFT(msg_buf & Msg_buf);
void getFFT(struct msg_buf & Msg_buf);

#endif //DEMON_FOURIER_PROCESSING_H
