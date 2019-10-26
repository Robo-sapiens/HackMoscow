#include "player.h"

Player::Player() {
    BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, 0);
}

Player::~Player() {
    BASS_Free();
}

void Player::play(char *fileName)
{    
    str = BASS_StreamCreateFile(FALSE, fileName, 0, 0, 0);
    BASS_ChannelPlay(str, false);
}

bool Player::initBass(int32_t hz) {

    BASS_Free();
    bool InitDefaultDevice = BASS_Init(-1, hz, BASS_DEVICE_DEFAULT, 0, 0);

    return InitDefaultDevice;
}

void Player::pause() {
    BASS_ChannelPause(str);
}

void Player::resume() {
    if (!BASS_ChannelPlay(str, false));
}

void Player::stop() {
    BASS_ChannelStop(str);
    BASS_StreamFree(str);
}