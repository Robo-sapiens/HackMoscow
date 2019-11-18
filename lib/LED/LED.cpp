//
// Created by antonrampage on 18.11.2019.
//

#include <iostream>
#include <rpi_ws281x/ws2811.h>
#include <unistd.h>

#include "LED.h"

static int rgb_to_hex(int r, int g, int b) {
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

LED::LED() {
    ledstring = {0, 0, 0, TARGET_FREQ, DMA, {GPIO_PIN, 0, LED_COUNT, STRIP_TYPE, 0, MAX_BRGHT}};
    try {
        ws2811_return_t ret;
        if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
            throw ret;
        }
    }
    catch(ws2811_return_t ret)
    {
        std::cout << "ws2811_init failed: " <<  ws2811_get_return_t_str(ret) << std::endl;
    }

    for (int i = 0; i < LED_COUNT; ++i) {
        ledstring.channel[0].leds[i] = 0x000000;
    }
}

LED::~LED() {
    ws2811_fini(&ledstring);
}

void LED::show_led_on_pi(RGB &led_rgb) {
    // left
    for (int i = LED_COUNT - 1; i >= UPDATE_LEDS + LED_COUNT / 2; --i) {
        this->ledstring.channel[0].leds[i] = this->ledstring.channel[0].leds[i - UPDATE_LEDS];
    }
    // right
    for (int i = 0; i < LED_COUNT / 2 - UPDATE_LEDS; ++i) {
        this->ledstring.channel[0].leds[i] = this->ledstring.channel[0].leds[i + UPDATE_LEDS];
    }
    // Set the left most updateLEDs with the new color
    for (int i = LED_COUNT / 2 - UPDATE_LEDS; i < LED_COUNT / 2 + UPDATE_LEDS; ++i) {
        this->ledstring.channel[0].leds[i] = rgb_to_hex(led_rgb.r, led_rgb.g, led_rgb.b);
    }

    ws2811_render(&this->ledstring);
}

#include <ws2811.h>

#define TARGET_FREQ                             WS2811_TARGET_FREQ
#define GPIO_PIN                                18
#define DMA                                     5
#define STRIP_TYPE                              WS2811_STRIP_RGB
#define LED_COUNT                               32
#define MAX_BRGHT                               40

#define UPDATE_LEDS                             3
#define DELAY                                   100000

typedef struct RGB {
    uint32_t r;
    uint32_t g;
    uint32_t b;
} RGB;

class LED {
public:
    LED();
    ~LED();
    void show_led_on_pi(RGB &led_rgb);
private:
    ws2811_t ledstring;
};


