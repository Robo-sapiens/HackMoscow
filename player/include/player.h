#ifndef __PLAYERH__
#define __PLAYERH__

#include <cstdint>
#include "bass.h"
#include "dirutils.h"
#include <string.h>

class Player
{
public:
    explicit Player();
    ~Player();

    void play(size_t number);
    void play(const string fileName);
    void pause();
    void resume();
    void stop();
    void setVolume(const float &vol);
    float getVolume();
    void setPosition(const float &pos);
    unsigned long getPosition();
    unsigned long getLength();
    float getRelativePosition();

    int getFFT(float *fft);

    void uploadFromDir(const char *dir);
    void showPlaylist();

    size_t getCurrentPlaylistPosition();
    string getMusicName();


private:
    static const int32_t HZ = 44100;

    HSAMPLE smp;
    HSTREAM str;

    size_t currentPlaylistPosition;
    float volume;
    bool InitDefaultDevice;

    std::vector<string> playList;

    bool initBass(int32_t hz);
    void parseFFT();
};

#endif