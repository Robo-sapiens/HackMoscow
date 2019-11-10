//
// Created by kira on 10.11.2019.
//

#include <pulse/simple.h>
#include <pulse/error.h>
#include <string>
#include <thread>

#include "fourier_processing.h"
#include "serial_talker.h"


int main(int argc, char ** argv) {
    /* The sample type to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_FLOAT32LE,
        .rate = 44100,
        .channels = 2
    };
    struct msg_buf Msg_buf;
    int error;
    /* Create the recording stream  */
    Msg_buf.s = pa_simple_new(nullptr, argv[0], PA_STREAM_RECORD,
                              "alsa_output.pci-0000_00_1b.0.analog-stereo.monitor",
                              "record", &ss, nullptr, nullptr, &error);
    if(!Msg_buf.s) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        return 1;
    }

//    std::thread t1(msg_sender, std::ref(Msg_buf));
    std::thread t2(parseFFT, std::ref(Msg_buf));
    std::thread t3(getFFT, std::ref(Msg_buf));
//    t1.join();
    t2.join();
    t3.join();

    if (Msg_buf.s) {
        pa_simple_free(Msg_buf.s);
    }
    return 0;
}
