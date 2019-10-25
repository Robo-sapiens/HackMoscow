#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "demon.h"

int main() {
    pid_t pid = fork(); // create child

    if (pid < -1) {
        printf("Error: Start Daemon failed (%s)\n", strerror(errno));
        exit(1);
    }

    if (pid) {
        exit(0);
    }

    umask(0); // take rights

    setsid(); // create new session

    chdir("/"); // cd /

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO); // close stdin, stdout, stderr, because they're not need

    demon();

    return 0;
}