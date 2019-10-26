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

private:
    static const int32_t HZ = 44100;

    bool initBass(int32_t hz);
};