#include "player.h"
#include "serial.h"
#include "uart.h"
#include "LED.h"
#define BAUDRATE 19200

Player::Player(size_t delay, const char *device) :
    delay(delay),
    device(device),
    rgb({0, 0, 0}),
    polygons(),
    verteces(3),
    base_polygon(new Point[verteces]),
    tr_matrix(new Point[2]),
    basic_mode(),
    led_(8, 32) {
    tr_matrix[0].x = 1.2;
    tr_matrix[0].y = 0;
    tr_matrix[1].x = 0;
    tr_matrix[1].y = 1.2;
}

Player::~Player() {
    delete[] base_polygon;
    delete[] tr_matrix;
}

void Player::render() {
    auto *tmp = new Polygon(verteces, rgb.r, rgb.g, rgb.b);
    tmp->set_items(base_polygon, verteces);
    polygons.push_back(tmp);

    for (auto &polygon : polygons) {
        if (verteces == 0) {
            led_.show_circle_on_led(polygon);
            polygon->radius *= 1.2;
        } else {
            led_.show_figure_on_led(polygon);
            polygon->operator*=(tr_matrix);
        }
    }
    auto last_item = polygons.front();
    if (last_item->max_item > 2 * led_.get_width()) {
        polygons.pop_front();
        delete last_item;
    }
}

void serial_interface(Player &player) {
    int32_t filed = serialport_init(player.device.c_str(), BAUDRATE);
    serialport_flush(filed);
    read_serial_port(filed, player);
    serialport_flush(filed);
    serialport_close(filed);
}

void show_leds(Player &player) {
    while (true) {
        if (player.basic_mode) {
            player.led_.show_led_on_pi(player.rgb);
        } else {
            player.render();
        }
        player.led_.render();
        usleep(player.delay);
    }
}
