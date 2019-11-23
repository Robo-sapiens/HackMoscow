#include <uart.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <mutex>
#include <termios.h>

std::mutex g_mutex;

#define LENGTH 11 // example - <rrrgggbbb> 

static bool is_num(char b) {
    char num[11] = "0123456789";
    for (int j = 0; j < 10; ++j) {
        if (b == num[j]) {
            return true;
        }
    }
    return false;
}    


static int read_with_markers(int32_t file, char s, char e, char *buf, int32_t length) {	
    memset(buf, 0, length + 1);

    char b[1];
    int i = 0;

    while(true) {
	while(read(file, b, 1) <= 0);

        if ((i == 0) && (b[0] != s)) {
            continue;
        }

	if ((i != 0) && (i < length - 1) && !is_num(b[0])) {
	    i = 0;
	    puts("no");
	    continue;
	}

        buf[i] = b[0];
        i++;

        if (b[0] == e) { 
            break;
        }
    }
    return 0;
}


static void parse_data(const char *buf, RGB &led_rgb, int32_t sum) {
    int32_t r = (buf[1] - '0') * 100 +
                (buf[2] - '0') * 10 +
                (buf[3] - '0');
    int32_t g = (buf[4] - '0') * 100 +
                (buf[5] - '0') * 10 +
                (buf[6] - '0');
    int32_t b = (buf[7] - '0') * 100 +
                (buf[8] - '0') * 10 +
                (buf[9] - '0');

    if (sum == (r + g +b)) {
        g_mutex.lock();
	led_rgb.r = r;
        led_rgb.g = g;
        led_rgb.b = b;
	//std::cout << "Received: SUM : " << sum << " r: "  << r << " g: " << g << " b: "  << b << std::endl;
        g_mutex.unlock();
    }
}


static void parse_sum(const char *buf, int32_t &sum) {
    sum = (buf[1] - '0') * 100 +
	  (buf[2] - '0') * 10 +
          (buf[3] - '0');
}


void read_serial_port(int32_t file, char s, char e, RGB &led_rgb) {
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(file, &rfds);

    auto buf = (char *)calloc(LENGTH + 1, sizeof(char));
    int32_t sum = 0;

    while (select(file + 1, &rfds, NULL, NULL, NULL) > 0) {
	read_with_markers(file, '{', '}', buf, 5);
        parse_sum(buf, sum);		
        read_with_markers(file, s, e, buf, LENGTH);
        parse_data(buf, led_rgb, sum);
	tcflush(file, TCIOFLUSH);
    }
}

