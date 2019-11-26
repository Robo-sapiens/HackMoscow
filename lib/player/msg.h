//
// Created by kira on 26.11.2019.
//

#ifndef PLAYER_UI_LIB_PLAYER_MSG_H_
#define PLAYER_UI_LIB_PLAYER_MSG_H_

#include <string>

class Msg {
public:
    Msg(size_t size);
    ~Msg();
    [[nodiscard]] int32_t actual_size() const;
    void set_default();
    void set_settings();
    int32_t sample_size;
    float *fft;
    std::string text;
};

#endif //PLAYER_UI_LIB_PLAYER_MSG_H_
