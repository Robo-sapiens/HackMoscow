#include <uart.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <cstring>

#define LENGTH 11 // example - <rrrgggbbb> 

static int read_with_markers(int32_t file, char s, char e, char *buf) {	
    memset(buf, 0, LENGHT);
    char b[1];
    int i = 0;
    while(read(fd, b, 1) > 0) {
	if ((i == 0) && (b[0] != s)) {
            return -1;
	}
	if ((b[0] != e) && (strlen(buf) < LENGTH)) {
	    return -1;
	}
        buffer[i] = b[0];
        i++;
	if (b[0] == e) {
	    break;
	}
    }
    return 0;
}

static void parse_data(char *buf, RGB &led_rgb) {
    led_rgb.r = (buf[1] - '0') * 100 +
                (buf[2] - '0') * 10 +
                (buf[3] - '0');
    led_rgb.g = (buf[4] - '0') * 100 +
                (buf[5] - '0') * 10 +
                (buf[6] - '0');
    led_rgb.b = (buf[7] - '0') * 100 +
                (buf[8] - '0') * 10 +
                (buf[9] - '0');
}


void read_serial_port(int32_t file, char s, char e, RGB &led_rgb) {
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    auto buf = (char *)calloc(LENGTH + 1, sizeof(char));
    while (select(fd + 1, &rfds, NULL, NULL, NULL) > 0) {
        if (read_with_markers(file, s, e, buf) == 0) {
	    parse_data(buf, led_rgb);
            printf("Received: R - %d, G - %d, B - %d\n", led_rgb.r, led_rgb.g, led_rgb.b);
	}
    }
}

