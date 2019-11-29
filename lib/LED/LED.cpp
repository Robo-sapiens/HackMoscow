//
// Created by antonrampage on 18.11.2019.
//

#include <iostream>
#include <rpi_ws281x/ws2811.h>
#include <vector>
#include <cmath>

#include "LED.h"

static inline int32_t rgb_to_hex(RGB &led_rgb) {
    return ((led_rgb.g & 0xff) << 16) + ((led_rgb.r & 0xff) << 8) + (led_rgb.b & 0xff);
}

LED::LED(int32_t width, int32_t length) :
    width(width),
    length(length) {
    ledstring = {0, 0, 0, TARGET_FREQ, DMA, {GPIO_PIN, 0, width * length, STRIP_TYPE, 0, MAX_BRGHT}};
    try {
        ws2811_return_t ret;
        if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
            throw ret;
        }
    }
    catch (ws2811_return_t ret) {
        std::cout << "ws2811_init failed: " << ws2811_get_return_t_str(ret) << std::endl;
    }

    for (int i = 0; i < width * length; ++i) {
        ledstring.channel[0].leds[i] = 0x000000;
    }
}

LED::~LED() {
    ws2811_fini(&ledstring);
}

void LED::show_led_on_pi(RGB &led_rgb) {
    // left
//	std::cout << led_rgb.r << ' ' << led_rgb.g << ' ' << led_rgb.b << std::endl;
    for (int i = width * length - 1; i >= width + width * length / 2; --i) {
        ledstring.channel[0].leds[i] = ledstring.channel[0].leds[i - width];
    }
    // right
    for (int i = 0; i < width * length / 2 - width; ++i) {
        ledstring.channel[0].leds[i] = ledstring.channel[0].leds[i + width];
    }
    // Set the left most updateLEDs with the new color
    for (int i = width * length / 2 - width; i < width * length / 2 + width; ++i) {
        ledstring.channel[0].leds[i] = rgb_to_hex(led_rgb);
    }
}

int32_t LED::transform_coord(int32_t x, int32_t y) {
    int centre = width * length / 2 - width / 2 - 1;
    int res = 0;
    if (x % 2 != 0) {
        res = (x == 0) ? centre : (centre + ((x * width) - y + 1));
    } else {
        res = centre + ((x * width) + y);
    }
    return res;
}

void LED::draw_line(Point &a_real, Point &b_real, RGB &led_rgb) {
    Point a = {a_real.x + 0.4f, a_real.y + 0.4f};
    Point b = {b_real.x + 0.4f, b_real.y + 0.4f};
    bool steep = (std::fabs(a.y - b.y) > std::fabs(a.x - b.x));
    if (steep) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }
    if (a.x > b.x) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }

    float dx = b.x - a.x;
    float dy = std::fabs(b.y - a.y);

    float error = dx / 2.0f;
    int y_step = (a.y < b.y) ? 1 : -1;
    int y = (int) a.y;

    const int max_x = (int) b.x;

    for (int x = (int) a.x; x <= max_x; x++) {
        if (steep) {
            if (((x <= width / 2) && (x >= -width / 2 + 1)) &&
                ((y <= length / 2) && (y >= -length / 2 + 1))) {
                ledstring.channel[0].leds[transform_coord(y, x)] = rgb_to_hex(led_rgb);
            }
        } else {
            if (((y <= width / 2) && (y >= -width / 2 + 1)) &&
               ((x <= length / 2) && (x >= -length / 2 + 1))) {
                ledstring.channel[0].leds[transform_coord(x, y)] = rgb_to_hex(led_rgb);
            }
        }
        error -= dy;
        if (error < 0) {
            y += y_step;
            error += dx;
        }
    }
}

void LED::show_figure_on_led(Polygon *polygon) {
    for (int i = 0; i < polygon->verteces; ++i) {
        if (i == polygon->verteces - 1) {
            draw_line(polygon->vectors[i], polygon->vectors[0], polygon->color);
        } else {
            draw_line(polygon->vectors[i], polygon->vectors[i + 1], polygon->color);
	}
    }
}

void LED::show_circle_on_led(const Polygon *polygon) {
//    polygon->vectors[0].x
//    polygon->vectors[0].y
//    polygon->radius
//    TODO(AntonRampage): translate coordinates to true center;
}

void LED::change_settings(int32_t width, int32_t length) {
    this->width = width;
    this->length = length;
    ws2811_fini(&ledstring);
    ledstring = {0, 0, 0, TARGET_FREQ, DMA, {GPIO_PIN, 0, width * length, STRIP_TYPE, 0, MAX_BRGHT}};
    try {
        ws2811_return_t ret;
        if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
            throw ret;
        }
    }
    catch (ws2811_return_t ret) {
        std::cout << "ws2811_init failed: " << ws2811_get_return_t_str(ret) << std::endl;
    }

    for (int i = 0; i < width * length; ++i) {
        ledstring.channel[0].leds[i] = 0x000000;
    }
}

void LED::render() {
    ws2811_render(&ledstring);
}

int32_t LED::get_width() const {
    return width;
}
