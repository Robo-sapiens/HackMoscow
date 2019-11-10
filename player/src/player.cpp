#include "player.h"
#include <iostream>
#include "../../arduino_lib/arduino_serial.h"
#include <cmath>

#define MIN_VAL 12
#define WIDTH 512
#define GAIN 1.15
#define DELAY 60000

//#define DEVICE "/dev/ttyACM0"  // could change but would rather not to
#define DEVICE "/dev/ttyUSB0"  // could change but would rather not to

// definitely changeable
#define FILTER 0 // [0..step = 0.001..0.05]
#define SLOPE 256  // [0..400]
#define RPEAK 0    // [0..1024]
#define GPEAK 512 // [0..1024]
#define BPEAK 256  // [0..1024]

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
    std::thread t3(command_parser, std::ref(*this));
    t1.join();
    t2.join();
    t3.join();
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
    return (float)level/4294967295.f;
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
        for (int i = std::max(0, RPEAK - WIDTH + SLOPE); i < std::min(1024, RPEAK + WIDTH - SLOPE); ++i) {
                r += (fft[i] > FILTER ? fft[i] : 0)
                        * (float)std::abs(WIDTH - SLOPE - (RPEAK - i)) / (WIDTH - SLOPE)
                        * 8 * (float)pow(2, (int)(RPEAK / 256));
        }
        for (int i = std::max(0, GPEAK - WIDTH + SLOPE); i < std::min(1024, GPEAK + WIDTH - SLOPE); ++i) {
                g += (fft[i] > FILTER ? fft[i] : 0)
                        * (float)std::abs(WIDTH - SLOPE - (GPEAK - i)) / (WIDTH - SLOPE)
                        * 8 * (float)pow(2, (int)(GPEAK / 256));
        }
        for (int i = std::max(0, BPEAK - WIDTH + SLOPE); i < std::min(1024, BPEAK + WIDTH - SLOPE); ++i) {
                b += (fft[i] > FILTER ? fft[i] : 0)
                        * (float)std::abs(WIDTH - SLOPE - (BPEAK - i)) / (WIDTH - SLOPE)
                        * 8 * (float)pow(2, (int)(BPEAK / 256));
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
        if (r < MIN_VAL && g < MIN_VAL && b < MIN_VAL) {
            r = std::pow(r, GAIN);
            g = std::pow(g, GAIN);
            b = std::pow(b, GAIN);
        }
	float min_val = std::min(r, std::min(g, b));
	r -= min_val;
	g -= min_val;
	b -= min_val;
        std::cout << r << ' ' << g << ' ' << b << std::endl;
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
    serialport_flush(filed);
    while (serialport_write(filed, player.msg.data()) != -1) {
        usleep(DELAY);
    }
    serialport_flush(filed);
    serialport_close(filed);
}


void command_parser(Player &player) {
    std::string command;
    while (true) {
        cin >> command;
        if (command == "exit") break;
        else if (command == "play") player.play(0);
        else if (command == "pause") player.pause();
        else if (command == "resume") player.resume();
        else if (command == "stop") player.stop();
        else if (command == "vol") {
            int param;
            cin >> param;
            player.setVolume((float)param / 100.f);
        }
        else if (command == "pos") {
            int param;
            cin >> param;
            player.setPosition((float)param / 100.f);
        }
        else if (command == "list") {
            player.showPlaylist();
        }
        else if (command == "info") {
            cout << "------------------" << '\n';
            cout << "Playing: " << player.getMusicName() << '\n';
            cout << "Volume: " << player.getVolume() << '\n';
            cout << "Position: " << player.getRelativePosition() << '\n';
            cout << "------------------" << '\n';
        }
        else if (command == "help") {
            cout << "------------------" << '\n';
            cout << "Available commands:" << '\n';
            cout << "- play" << '\n';
            cout << "- pause" << '\n';
            cout << "- resume" << '\n';
            cout << "- stop" << '\n';
            cout << "- vol <0-100:volume>" << '\n';
            cout << "- pos <0-100:position>" << '\n';
            cout << "- info" << '\n';
            cout << "- help" << '\n';
            cout << "- list" << '\n';
            cout << "- ch <number>" << '\n';
            cout << "------------------" << '\n';
        } else if (command == "ch") {
            int number;
            cin >> number;
            player.play(number);
        }
    }
}
