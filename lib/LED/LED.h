//
// Created by antonrampage on 18.11.2019.
//

#ifndef PLAYER_LED_H
#define PLAYER_LED_H


#include <rpi_ws281x/ws2811.h>

#define TARGET_FREQ                             WS2811_TARGET_FREQ
#define GPIO_PIN                                21
#define DMA                                     5
#define STRIP_TYPE                              WS2811_STRIP_RGB
#define LED_COUNT                               256 // TODO: AS PARAM
#define MAX_BRGHT                               40

#define UPDATE_LEDS                             8

typedef struct RGB {
    int32_t r;
    int32_t g;
    int32_t b;
} RGB;

class LED {
public:
    LED();
    ~LED();
    void show_led_on_pi(RGB &led_rgb);
private:
    ws2811_t ledstring;
};



#endif //PLAYER_LED_H
