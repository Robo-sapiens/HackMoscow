//
// Created by antonrampage on 17.11.2019.
//

#include <iostream>
#include <ws2811.h>
#include <unistd.h>
/*
    Defines für ws2811 LED Stripes
*/

#define TARGET_FREQ                             WS2811_TARGET_FREQ
#define GPIO_PIN                                18
#define DMA                                     5
#define STRIP_TYPE                              WS2811_STRIP_RGB        // WS2812/SK6812RGB integrated chip+leds
#define LED_COUNT                               10

ws2811_led_t dotcolors[] =
        {
                0x00200000,  // red
                0x00201000,  // orange
                0x00202000,  // yellow
                0x00002000,  // green
                0x00002020,  // lightblue
                0x00000020,  // blue
                0x00100010,  // purple
                0x00200010,  // pink
        };

ws2811_led_t dotcolors_rgbw[] =
        {
                0x00200000,  // red
                0x10200000,  // red + W
                0x00002000,  // green
                0x10002000,  // green + W
                0x00000020,  // blue
                0x10000020,  // blue + W
                0x00101010,  // white
                0x10101010,  // white + W

        };

// settings for led (там более менее все понятно) ну выше есть дефайны а так смотреть в ws2811.h
ws2811_t ledstring =
        {
                .device = 0,
                .rpi_hw = 0,
                .freq = TARGET_FREQ,
                .dmanum = DMA,
                GPIO_PIN,
                0,
                LED_COUNT,
                STRIP_TYPE,
                0,
                255
        };

int main()
{
    ws2811_init(&ledstring);

    int c = 0;

    for (int i = 0; i < LED_COUNT; i++)
    {
        if (ledstring.channel[0].strip_type == SK6812_STRIP_RGBW) {
            ledstring.channel[0].leds[i] = dotcolors_rgbw[c];
        }
        else {
            ledstring.channel[0].leds[i] = dotcolors[c];
        }
        c++;

        ws2811_render(&ledstring);

        if (c == sizeof(dotcolors))
        {
            c = 0;
        }

        usleep(1000000);
    }
    return 0;
}

