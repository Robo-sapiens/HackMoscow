#include <iostream>
#include "player.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Usage: [send delay(=60000)] [device(serial port)]\n"
                     "  fft options: [sample size]" << std::endl;
        return 1;
    }
    RGBParameters params = {
            .width = 512,
            .filter = 0, // [0..step=0.001..0.05]
            .slope = 256, // [0..width]
            .red_peak = 0,    // [0..1024]
            .green_peak = 512, // [0..1024]
            .blue_peak = 256  // [0..1024]
    }; // TODO

    Player player(std::atoi(argv[1]), argv[2], std::atoi(argv[3]), params);
    std::thread t1(get_fft, std::ref(player));
    std::thread t2(parse_fft, std::ref(player));
    std::thread t3(msg_sender, std::ref(player));
    t1.join();
    t2.join();
    t3.join();
    return 0;
}