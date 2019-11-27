//
// Created by antonrampage on 18.11.2019.
//

#ifndef PLAYER_LED_H
#define PLAYER_LED_H

#include <rpi_ws281x/ws2811.h>
#include <cmath>
#include <vector>
#include <player/polygon.h>

#define TARGET_FREQ                             WS2811_TARGET_FREQ
#define GPIO_PIN                                21
#define DMA                                     5
#define STRIP_TYPE                              WS2811_STRIP_RGB
#define MAX_BRGHT                               255


typedef struct RGB {
    int32_t r;
    int32_t g;
    int32_t b;
} RGB;

typedef struct Point {
    float_t x;
    float_t y;
} Point;

class LED {
public:
    LED(int32_t width, int32_t length);
    ~LED();
    void show_led_on_pi(RGB &led_rgb);
    void show_figure_on_led(const Polygon *polygon);
    void show_circle_on_led(const Polygon *polygon);
    void draw_line(Point &a, Point &b, RGB &led_rgb);
    int32_t get_width() const;
    void change_settings(int32_t width, int32_t length);
    void render();
private:
    int32_t transform_coord(int32_t x, int32_t y);
    ws2811_t ledstring;
    int32_t width;
    int32_t length;
};

#endif //PLAYER_LED_H
