#include "player.h"
#include <iostream>

Player::Player() {
    initBass(HZ);
    currentPlaylistPosition - 0;
}

Player::~Player() {
    BASS_Free();
}

void Player::play(size_t number)
{
    if (!playList.empty() && number < playList.size())
        play(playList.at(number).c_str());
}

void Player::play(const string fileName)
{
    stop();
    str = BASS_StreamCreateFile(FALSE, fileName.c_str(), 0, 0, 0);
    BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, 1.0);
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

void Player::setVolume(const float &vol) {
    // min volume: 0.0
    // max volume: 1.0
    if (vol > 1.0)
        volume = 1.0;
    else if (vol < 0)
        volume = 0.0;
    else
        volume = vol;
    BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, volume);
}

float Player::getVolume() {
    long level = BASS_ChannelGetLevel(str);
    return (float)level/4294967295;
}

void Player::setPosition(const float &pos) {
    if (pos > 0.0) {
        unsigned long position = BASS_ChannelSeconds2Bytes(str, pos * getLength());
        std::cout << position << "\n" << getLength() << '\n';
        BASS_ChannelSetPosition(str, position, BASS_POS_BYTE);
    }
}

unsigned long Player::getPosition() {
    unsigned long pos = BASS_ChannelGetPosition(str, BASS_POS_BYTE);
    unsigned long posSec = (unsigned long)BASS_ChannelBytes2Seconds(str, pos);

    return posSec;
}

unsigned long Player::getLength() {
    long TimeBytes = BASS_ChannelGetLength(str, BASS_POS_BYTE);
    double Time = BASS_ChannelBytes2Seconds(str, TimeBytes);

    return (int)Time;
}

float Player::getRelativePosition() {
    return (float)getPosition() / getLength();
}

float* Player::getFFT(float *fft){
    BASS_ChannelGetData(str, fft, BASS_DATA_FFT2048);
    return fft;
}

void Player::showPlaylist() {
    std::cout << "---Playlist---" << '\n';
    for (size_t i = 0; i < playList.size(); ++i) {
        std::cout << i << ": " << playList.at(i) << '\n';
    }
}

void Player::uploadFromDir(const char *dir) {
    cout << "parsing" << '\n';
    UD::parse_dir(playList, dir);
}

size_t Player::getCurrentPlaylistPosition() {
    return currentPlaylistPosition;
}

string Player::getMusicName() {
    if(!playList.empty())
        return playList.at(currentPlaylistPosition);
}
