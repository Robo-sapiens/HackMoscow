#include "player.h"
#include <iostream>
#include <arduino_serial.h>
#include <cmath>

#define DEVICE "/dev/ttyUSB0"
#define PEAK 1024
#define MIN_VAL 12
#define FILTER 4
#define GAIN 1.1

std::mutex g_lock;


Player::Player() : msg("<000000000>") {
    initBass(HZ);
    currentPlaylistPosition = 0;
}

Player::~Player() {
    BASS_Free();
}

void Player::play(size_t number) {
    if (!playList.empty() && number < playList.size())
        play(playList.at(number).c_str());
}

void Player::play(const string fileName) {
    stop();
    str = BASS_StreamCreateFile(FALSE, fileName.c_str(), 0, 0, 0);
    BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, 1.0);
    BASS_ChannelPlay(str, false);
    this->msg = "<000000000>";

    std::thread t1(msg_sender, std::ref(*this));
    std::thread t2(parseFFT, std::ref(*this));
    t1.join();
    t2.join();
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
    BASS_ChannelPlay(str, false);
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

int Player::getFFT(float *fft){
    return BASS_ChannelGetData(str, fft, BASS_DATA_FFT2048);
}

void parseFFT(Player &player) {
    auto * fft = new float[1024];
    while (player.getFFT(fft) != -1) {
        float r = 0, g = 0, b = 0;
        for (int i = 0; i < PEAK; ++i) {
            r += fft[i] * ((float) (PEAK - i) / PEAK) * 16;
        }
        for (int j = 0; j < PEAK / 2; ++j) {
            g += fft[j] * ((float) j / PEAK) * 64;
        }
        for (int k = PEAK / 2; k < PEAK; ++k) {
            g += fft[k] * ((float) (PEAK - k) / PEAK) * 64;
        }
        for (int l = 0; l < PEAK; ++l) {
            b += fft[l] * ((float) l / PEAK) * 128;
        }
        if (r > 255) {
            r = 255;
        }
        if (g > 255) {
            g = 255;
        }
        if (b > 255) {
            b = 255;
        }
        if (r < MIN_VAL && g < MIN_VAL && b < MIN_VAL
//        && r > FILTER_RGB && g > FILTER_RGB && b > FILTER_RGB
            ) {
//            float tmp = std::max(std::max(r, g), b);
//            r = r / tmp * MIN_VAL;
//            g = g / tmp * MIN_VAL;
//            b = b / tmp * MIN_VAL;
            r = std::pow(r, GAIN);
            g = std::pow(g, GAIN);
            b = std::pow(b, GAIN);
        }
        g_lock.lock();
        player.msg[1] = '0' + (char)((int)r / 100);
        player.msg[2] = '0' + (char)((int)r / 10 % 10);
        player.msg[3] = '0' + (char)((int)r % 10);
        player.msg[4] = '0' + (char)((int)g / 100);
        player.msg[5] = '0' + (char)((int)g / 10 % 10);
        player.msg[6] = '0' + (char)((int)g % 10);
        player.msg[7] = '0' + (char)((int)b / 100);
        player.msg[8] = '0' + (char)((int)b / 10 % 10);
        player.msg[9] = '0' + (char)((int)b % 10);
        g_lock.unlock();
    }
    delete[] fft;
}

void msg_sender(Player & player) {
    int filed = serialport_init(DEVICE, 9600);
    while (serialport_write(filed, player.msg.data()) != -1) {
        usleep(50000);
    }
    serialport_flush(filed);
    serialport_close(filed);
}
