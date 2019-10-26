#include "player.h"

Player::Player() {

}

void Player::play(char *fileName)
{
    HSAMPLE smp;
    HSTREAM str;

    BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, 0);
    str = BASS_StreamCreateFile(FALSE, fileName, 0, 0, 0);
    BASS_ChannelPlay(str, false);
}

bool Player::initBass(int32_t hz) {

    BASS_Free();
    bool InitDefaultDevice = BASS_Init(-1, hz, BASS_DEVICE_DEFAULT, 0, 0);

    return InitDefaultDevice;
}

void Player::pause() {
    
}

void Player::resume() {

}

void Player::stop() {

}