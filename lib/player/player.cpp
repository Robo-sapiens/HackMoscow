#include "player.h"

#define FREQ 44100

Player::Player(size_t delay)
    : delay(delay),
      msg(SAMPLE_SIZE),
      rgb({0, 0, 0}),
      error_code(0),
      hsample(),
      hstream(),
      rgb_parameters(),
      capture_device() {
//    HINSTANCE bass = LoadLibrary("BASS.DLL"); // load BASS
//    BASS_Init = reinterpret_cast<WINBOOL (*)(int, DWORD, DWORD, HWND, const GUID *)>(GetProcAddress(bass, "BASS_Init")); // get BASS_Init
    if (!(BASS_Init(0, FREQ, BASS_DEVICE_LOOPBACK, NULL, NULL))) {
        error_handler();
    }
    hstream = BASS_StreamCreate(44100, 2, BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, NULL);
    error_handler();
}

Player::~Player() {
    BASS_Free();
}

void Player::error_handler() {
    this->error_code = BASS_ErrorGetCode();
    std::cout << "error code is: " << (int32_t) this->error_code << std::endl;
    switch (this->error_code) {
        case BASS_ERROR_UNKNOWN:std::cout << "everything is suspicious, hmmmm...." << std::endl;
            break;
        case BASS_OK:std::cout << "everything is ok, hmmmm...." << std::endl;
            break;
        case BASS_ERROR_MEM:std::cout << "memory, my dude" << std::endl;
            break;
        case BASS_ERROR_FILEOPEN:std::cout << "couldn't open file :(" << std::endl;
            break;
        case BASS_ERROR_DRIVER:std::cout << "driver error :(" << std::endl;
            break;
        case BASS_ERROR_BUFLOST:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_HANDLE:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_FORMAT:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_POSITION:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_INIT:std::cout << "did not initialize, hmmmm..." << std::endl;
            break;
        case BASS_ERROR_START:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_SSL:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_ALREADY:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOCHAN:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_ILLTYPE:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_ILLPARAM:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NO3D:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOEAX:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_DEVICE:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOPLAY:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_FREQ:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOTFILE:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOHW:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_EMPTY:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NONET:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_CREATE:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOFX:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_NOTAVAIL:std::cout << "BASS_ERROR_NOTAVAIL :(" << std::endl;
            break;
        case BASS_ERROR_DECODE:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_DX:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_TIMEOUT:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_FILEFORM:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_SPEAKER:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_VERSION:std::cout << " :(" << std::endl;
            break;
        case BASS_ERROR_CODEC:std::cout << "BASS_ERROR_CODEC :(" << std::endl;
            break;
        case BASS_ERROR_ENDED:std::cout << "BASS_ERROR_ENDED :(" << std::endl;
            break;
        case BASS_ERROR_BUSY:std::cout << "BASS_ERROR_BUSY :(" << std::endl;
            break;
        default:std::cout << "error code isn't even unknown, hmmmm...." << std::endl;
            break;
    }
}
