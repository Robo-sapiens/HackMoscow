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
    float width;
    float filter;
    float slope;
    float red_peak;
    float green_peak;
    float blue_peak;
} RGBParameters;

class Player
{
    class Msg
    {
    public:
        Msg(std::string what, size_t size);
        ~Msg();
        size_t sample_size;
        float * fft;
        std::string text;
    };
public:
    explicit Player(size_t delay, const char * device, size_t sample_size, RGBParameters params);
    ~Player();

    void error_handler();

    size_t delay;
    std::string device;
    Msg msg;
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

void get_fft(Player &msg);
void msg_sender(Player &player);
void parse_fft(Player &player);

#endif