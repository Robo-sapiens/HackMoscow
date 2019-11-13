#include <iostream>
#include "player.h"

#define SAMPLE_SIZE 512  // connected to BASS_FFT_1024
#define WITHOUT_GUI

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Usage: [send delay(=60000usec)] [device(serial port)]\n" << std::endl;
        return 1;
    }

    RGBParameters params = {
            .width = SAMPLE_SIZE / 2,    // [0..SAMPLE_SIZE]
            .filter = 0,                 // [0..idk]
            .red_peak = 0,               // [0..SAMPLE_SIZE] [0..100%]
            .green_peak = 512,           // [0..SAMPLE_SIZE] [0..100%]
            .blue_peak = 256,            // [0..SAMPLE_SIZE] [0..100%]
            .sensitivity = 255. / 5000, // [0..idk]
            .tweak_by_min = false         //
    };

    Player player(std::atoi(argv[1]), argv[2], SAMPLE_SIZE, params);
    std::thread t1(get_fft, std::ref(player));
    std::thread t2(parse_fft, std::ref(player));
    std::thread t3(msg_sender, std::ref(player));
    t1.join();
    t2.join();
    t3.join();
    return 0;
}