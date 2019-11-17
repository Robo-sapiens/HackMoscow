#ifndef __PLAYERH__
#define __PLAYERH__

#include "capture.h"
#include "bass.h"
#include <thread>
#include <mutex>
#include <string>
#include <cstdint>
#include <cmath>


typedef struct RGBParameters
{
    int32_t  width;
    int32_t  filter;
    int32_t  red_peak;
    int32_t  green_peak;
    int32_t  blue_peak;
    double_t sensitivity;
    bool     tweak_by_min;
} RGBParameters;

class Player
{
    class Msg
    {
    public:
        Msg(std::string what, size_t size);
        ~Msg();
        int32_t sample_size;
        float * fft;
        std::string text;
    };

    typedef struct RGB
    {
        int32_t r;
        int32_t g;
        int32_t b;
    } RGB;

public:
    explicit Player(size_t delay, size_t sample_size, RGBParameters params);
    ~Player();

    void error_handler();
    void tweak_rgb(RGBParameters rgb_params);

    size_t delay;
    Msg msg;
    RGB rgb;
    int8_t error_code;
    HSAMPLE hsample;
    HSTREAM hstream;
    RGBParameters rgb_parameters;
    pa::Capture capture_device;
private:
    // singleton
    Player &operator=(Player const &);

    Player (Player const &);
};

#endif