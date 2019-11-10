//
// Created by kira on 09.11.2019.
//

#ifndef DEMON_SERIAL_TALKER_H
#define DEMON_SERIAL_TALKER_H

#include <pulse/simple.h>
#include <string>


struct msg_buf {
    msg_buf() : s(nullptr), fft(nullptr), msg("<000000000>") {};
    pa_simple * s;
    float * fft;
    std::string msg;
};

void msg_sender(msg_buf & Msg_buf);


#endif //DEMON_SERIAL_TALKER_H
