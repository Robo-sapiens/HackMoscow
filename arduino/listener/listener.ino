#include <Arduino.h>
#include <FastLED.h>


#define updateLEDS 1 // Number of LEDS to update every millisecond

#define NUM_LEDS 100 // Number of LEDS in a strip with default value

CRGB leds[NUM_LEDS];

// Number of control pin on Arduino
#define LED_PIN 13


void recv();
void parse_new_data();
void led_show();

struct msg {
    char * received_chars;
    boolean new_data;
    char start_marker;
    char end_marker;
};

const byte msg_size = 32;
char received_chars[msg_size];
char received_cmds[msg_size];
struct msg msg_continuous;
struct msg msg_cmd;

struct colors {
    int r;
    int g;
    int b;
};

struct colors led_rgb = {0,0,0}; 


void setup() {
    msg_continuous = {received_chars, false, '<', '>'};
    msg_cmd = {received_cmds, false, '{', '}'};

    Serial.begin(9600);
    
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

    for (int i = 0; i < NUM_LEDS ; ++i) {
        leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}

void loop() {
    recv();
    parse_new_data();
    led_show();
    delay(20);
}

void recv() {
    static boolean recv_in_progress = false;
    static byte ndx = 0;
    byte rc;

    if (msg_continuous.new_data) {
        return;
    }
    while (Serial.available() > 0) {
        rc = Serial.read();

        if (recv_in_progress) {
            if (rc != msg_continuous.end_marker) {
                received_chars[ndx] = rc;
                ndx++;
                if (ndx >= msg_size) {
                    ndx = msg_size - 1;
                }
            } else {
                received_chars[ndx] = '\0'; // terminate the string
                recv_in_progress = false;
                ndx = 0;
                msg_continuous.new_data = true;
            }
        } else if (rc == msg_continuous.start_marker) {
            recv_in_progress = true;
        }
    }
}

void parse_new_data() {
    if (!msg_continuous.new_data) {
        return;
    }
    for (int i = 0; i < 9; ++i) {
        Serial.println(msg_continuous.received_chars[i]);
    }
    led_rgb.r = (msg_continuous.received_chars[0] - '0') * 100 +
                (msg_continuous.received_chars[1] - '0') * 10 +
                (msg_continuous.received_chars[2] - '0');
    led_rgb.g = (msg_continuous.received_chars[3] - '0') * 100 +
                (msg_continuous.received_chars[4] - '0') * 10 +
                (msg_continuous.received_chars[5] - '0');
    led_rgb.b = (msg_continuous.received_chars[6] - '0') * 100 +
                (msg_continuous.received_chars[7] - '0') * 10 +
                (msg_continuous.received_chars[8] - '0');
    
    if (led_rgb.r < 0) {
        led_rgb.r = 0;
    }
    if (led_rgb.g < 0) {
        led_rgb.g = 0;
    }
    if (led_rgb.b < 0) {
        led_rgb.b = 0;
    }
    if (led_rgb.r > 255) {
        led_rgb.r = 255;
    }
    if (led_rgb.r > 255) {
        led_rgb.r = 255;
    }
    if (led_rgb.r > 255) {
        led_rgb.r = 255;
    }
    
    Serial.println(led_rgb.r);
    Serial.println(led_rgb.g);
    Serial.println(led_rgb.b);
    msg_continuous.new_data = false;
}


void led_show() {
    // Shift all LEDs to the right by updateLEDS number each time
    for (int i = NUM_LEDS - 1; i >= updateLEDS; --i) {
        leds[i] = leds[i - updateLEDS];
    }
    // Set the left most updateLEDs with the new color
    for (int i = 0; i < updateLEDS; ++i) {
        leds[i] = CRGB(led_rgb.r, led_rgb.g, led_rgb.b);
    }
    FastLED.show();
    led_rgb.r = 0;
    led_rgb.g = 0;
    led_rgb.b = 0;
}
