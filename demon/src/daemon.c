//
// Created by antonrampage on 25.10.2019.
//

#include "daemon.h"
#include <stdio.h>
#include <bass.h>
#include <stdbool.h>
#include <string.h>

void daemon_func() {
//    DWORD chan;

    if (!BASS_RecordInit(-1)) {
        printf("error");
        return;
    }
//    chan = BASS_RecordStart(44100, 2, 0, 0, 0); // Recording Channel
//    if ((!r_init) || (!chan)) {
//        BASS_Free();
//    }
    printf("her\n");

    char *str = "";
    for (int i = 0; str = BASS_RecordInit(i); i++) {
        printf("%s\n", str);
    }
//    printf("f\n");
//    while (!str) {
//        printf("%s\n", str);
//        ++a;
//        str = strdup(BASS_RecordGetInputName(a));
//    }
    printf("f\n");
}
