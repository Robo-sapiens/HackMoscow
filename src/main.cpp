#include <iostream>
#include "player.h"

#define SAMPLE_SIZE 512  // connected to
#define DELAY 70000


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Serial port undefined";
    }

    RGBParameters params = {
            .width = SAMPLE_SIZE / 4,    // [0..SAMPLE_SIZE]
            .filter = 0,                 // [0..idk]
            .red_peak = 0,               // [0..SAMPLE_SIZE] [0..100%]
            .green_peak = 128,           // [0..SAMPLE_SIZE] [0..100%]
            .blue_peak = 256,            // [0..SAMPLE_SIZE] [0..100%]
            .sensitivity = 255. / 5000, // [0..idk]
            .tweak_by_min = false         //
    };

    Player player(DELAY, argv[1], SAMPLE_SIZE, params);
    std::thread t1(get_fft, std::ref(player));
    std::thread t2(parse_fft, std::ref(player));
//    std::thread t3(serial_interface, std::ref(player));
    std::thread t4(show_leds, std::ref(player));
    t1.join();
    t2.join();
//    t3.join();
    t4.join();
    return 0;
}