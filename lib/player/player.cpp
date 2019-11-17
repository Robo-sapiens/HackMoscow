#include <iostream>
#include <cmath>
#include <utility>
#include <mutex>

#include "player.h"
#include "serial.h"

#define BAUDRATE 19200
#define FREQ 44100

std::mutex g_lock;


Player::Player(size_t delay, const char * device, size_t sample_size, RGBParameters params) :
delay(delay), device(device), msg("<000000000>", sample_size), rgb({0, 0, 0}), error_code(0), hsample(), hstream(),
rgb_parameters(params), capture_device() {
    if (!(BASS_Init(0, FREQ, BASS_DEVICE_LOOPBACK, NULL, NULL))) {
        error_handler();
    }
    hstream = BASS_StreamCreate(44100, 2, BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, NULL);
    error_handler();
}


Player::~Player() {
    BASS_Free();
}


Player::Msg::Msg(std::string what, size_t sample_size) :
        sample_size(sample_size), fft((float*)calloc(sample_size, sizeof(float))), text(std::move(what)) {}


Player::Msg::~Msg() {
    free(fft);
}


void get_fft(Player &player) {
    auto in = (float *)calloc(player.msg.sample_size, sizeof(float));
    while (true) {
        player.capture_device.get_sample(in, player.msg.sample_size);
        BASS_StreamPutData(player.hstream, in, player.msg.sample_size);
        if (BASS_ChannelGetData(player.hstream, player.msg.fft, BASS_DATA_FFT1024) == -1) {
            break;
        }
    }
    free(in);
    player.error_handler();
}


void parse_fft(Player &player) {
    auto p = player.rgb_parameters;
    while (!player.error_code) {
        int32_t r = 0, g = 0, b = 0;
        for (int32_t i = std::max(0, p.red_peak - p.width);
        i < std::min(player.msg.sample_size, p.red_peak + p.width); ++i) {
            if (player.msg.fft[i] > p.filter) {
                r += player.msg.fft[i] * std::abs(p.width - (p.red_peak -   (float)i)) / (p.width) * i;
            }
        }
        for (int32_t i = std::max(0, p.green_peak - p.width);
        i < std::min(player.msg.sample_size, p.green_peak + p.width); ++i) {
            if (player.msg.fft[i] > p.filter) {
                g += player.msg.fft[i] * std::abs(p.width - (p.green_peak - (float)i)) / (p.width) * i;
            }
        }
        for (int32_t i = std::max(0, p.blue_peak - p.width);
        i < std::min(player.msg.sample_size, p.blue_peak + p.width); ++i) {
            if (player.msg.fft[i] > p.filter) {
                b += player.msg.fft[i] * std::abs(p.width - (p.blue_peak -  (float)i)) / (p.width) * i;
            }
        }
        if (p.tweak_by_min) {
            int32_t min_val = std::min(r, std::min(g, b));
            r -= min_val;
            g -= min_val;
            b -= min_val;
        }
        r *= p.sensitivity;
        g *= p.sensitivity;
        b *= p.sensitivity;
        if (r > 255) {
            r = 255;
        }
        if (g > 255) {
            g = 255;
        }
        if (b > 255) {
            b = 255;
        }
        std::cout << r << ' ' << g << ' ' << b << std::endl;
        g_lock.lock();
        player.rgb.r = r;
        player.rgb.g = g;
        player.rgb.b = b;
        g_lock.unlock();
    }
}


void serial_interface(Player &player) {
    int32_t filed = serialport_init(player.device.c_str(), BAUDRATE);
    serialport_flush(filed);
    while (serialport_write(filed, player.msg.text.c_str()) != -1) {
        usleep(player.delay);
    }
    serialport_flush(filed);
    serialport_close(filed);
}

void show_leds(Player &player) {

}

void Player::error_handler() {
    this->error_code = BASS_ErrorGetCode();
    std::cout << "error code is: " << (int32_t)this->error_code << std::endl;
    switch (this->error_code) {
        case BASS_ERROR_UNKNOWN:
            std::cout << "everything is suspicious, hmmmm...." << std::endl;
            break;
        case BASS_OK:
            std::cout << "everything is ok, hmmmm...." << std::endl;
            break;
        case BASS_ERROR_MEM:
            std::cout << "memory, my dude" << std::endl;
            break;
        case BASS_ERROR_FILEOPEN:
            std::cout << "couldn't open file :(" << std::endl;
            break;
        case BASS_ERROR_DRIVER:
            std::cout << "driver error :(" << std::endl;
            break;
        case BASS_ERROR_BUFLOST:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_HANDLE:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_FORMAT:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_POSITION:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_INIT:
            std::cout << "did not initialize, hmmmm..." << std::endl;
            break;
        case BASS_ERROR_START:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_SSL:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_ALREADY:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOCHAN:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_ILLTYPE:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_ILLPARAM:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NO3D:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOEAX:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_DEVICE:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOPLAY:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_FREQ:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOTFILE:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOHW:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_EMPTY:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NONET:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_CREATE:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOFX:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOTAVAIL:
            std::cout << "BASS_ERROR_NOTAVAIL :(" << std::endl;
            break;
        case BASS_ERROR_DECODE:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_DX:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_TIMEOUT:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_FILEFORM:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_SPEAKER:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_VERSION:
            std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_CODEC:
            std::cout << "BASS_ERROR_CODEC :(" << std::endl;
            break;
        case BASS_ERROR_ENDED:
            std::cout << "BASS_ERROR_ENDED :(" << std::endl;
            break;
        case BASS_ERROR_BUSY:
            std::cout << "BASS_ERROR_BUSY :(" << std::endl;
            break;
        default:
            std::cout << "error code isn't even unknown, hmmmm...." << std::endl;
            break;
    }
}
