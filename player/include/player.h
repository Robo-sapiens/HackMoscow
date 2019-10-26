#pragma once

#include <stdint.h>
#include "bass.h"

class Player
{
public:
    explicit Player();
    ~Player();

    void play(char *fileName);
    void pause();
    void resume();
    void stop();
    void setVolume(const float &vol);
    float getVolume();
    void setPosition(const float &pos);
    unsigned long getPosition();
    unsigned long getLength();
    float getRelativePosition();

private:
    static const int32_t HZ = 44100;

    HSAMPLE smp;
    HSTREAM str;

    float volume;

    bool InitDefaultDevice;

    bool initBass(int32_t hz);
};