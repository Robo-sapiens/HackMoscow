//
// Created by antonrampage on 18.11.2019.
//

#include <iostream>
#include <rpi_ws281x/ws2811.h>
#include <unistd.h>
#include <vector>
#include <cmath>

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
//	std::cout << led_rgb.r << ' ' << led_rgb.g << ' ' << led_rgb.b << std::endl;
    for (int i = LED_COUNT - 1; i >= UPDATE_LEDS + LED_COUNT / 2; --i) {
        this->ledstring.channel[0].leds[i] = this->ledstring.channel[0].leds[i - UPDATE_LEDS];
    }
    // right
    for (int i = 0; i < LED_COUNT / 2 - UPDATE_LEDS; ++i) {
        this->ledstring.channel[0].leds[i] = this->ledstring.channel[0].leds[i + UPDATE_LEDS];
    }
    // Set the left most updateLEDs with the new color
    for (int i = LED_COUNT / 2 - UPDATE_LEDS; i < LED_COUNT / 2 + UPDATE_LEDS; ++i) {
        this->ledstring.channel[0].leds[i] = rgb_to_hex(led_rgb.g, led_rgb.r, led_rgb.b);
    }

    ws2811_render(&this->ledstring);
}

static int transform_coord(int x, int y) {
    int centre = LED_COUNT / 2 - UPDATE_LEDS / 2 - 1;
    int res = 0;
    if (x % 2 != 0) {
	res = (x == 0) ? centre : (centre + ((x * UPDATE_LEDS) - y + 1));
    } else {
        res = centre + ((x * UPDATE_LEDS) + y);
    }
    std::cout << res << std::endl;
    return res;
}    

void LED::draw_line(Point &a, Point &b, RGB &led_rgb) {
    bool steep = (fabs(a.y - b.y) > fabs(a.x - b.x));
    if (steep) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }
    if (a.x > b.x) {
	std::swap(a.x, b.x);
	std::swap(a.y, b.y);
    }
 
    float dx = b.x - a.x;
    float dy = fabs(b.y - a.y);
 
    float error = dx / 2.0f;
    int y_step = (a.y < b.y) ? 1 : -1;
    int y = (int)a.y;
 
    const int max_x = (int)b.x;
 
    for(int x = (int)a.x; x <= max_x; x++) {
	if (steep) {
	    this->ledstring.channel[0].leds[transform_coord(y, x)] = rgb_to_hex(led_rgb.g, led_rgb.r, led_rgb.b);
	} else {
            this->ledstring.channel[0].leds[transform_coord(x, y)] = rgb_to_hex(led_rgb.g, led_rgb.r, led_rgb.b);
	}
        std::cout << x << ' ' << y << std::endl;
        error -= dy;
        if (error < 0) {
	    y += y_step;
            error += dx;
	}
    }
    ws2811_render(&this->ledstring);

}
	


void LED::show_figure_on_led(std::vector<std::pair<std::vector<Point>, RGB>> &figures) {}	


