//
// Created by kira on 26.11.2019.
//

#ifndef PLAYER_UI_LIB_PLAYER_MSG_H_
#define PLAYER_UI_LIB_PLAYER_MSG_H_

#include <string>
#include <cmath>

class Msg {
public:
    explicit Msg(size_t size);
    ~Msg();
    [[nodiscard]] int32_t actual_size() const;
    void set_default();
    void set_settings(int32_t mode, int32_t verteces, const float *x, const float *y, int32_t bpm, float_t rotation);
    void set_new_led(int32_t width, int32_t length);
    int32_t sample_size;
    float_t *fft;
    std::string text;
    bool is_settings;
};

#endif //PLAYER_UI_LIB_PLAYER_MSG_H_
