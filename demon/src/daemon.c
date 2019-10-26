//
// Created by antonrampage on 25.10.2019.
//

#include "daemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <bass.h>
#include <stdbool.h>
#include <string.h>

DWORD output;
DWORD input;
int prebuf;

BOOL CALLBACK RecordProc(HRECORD handle, const void *buffer, DWORD length, void *user) {
    BASS_StreamPutData(output, buffer, length);
    printf("%p", buffer);
    if (prebuf > 0) {
        prebuf -= length;
        if (prebuf <= 0) {
            BASS_ChannelPlay(output, FALSE);
        }
    }
    return TRUE;
}

void daemon_func() {
    FILE *file = fopen("file.wav", "a");
    if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
        printf("An incorrect version of BASS was loaded");
        return;
    }

    // initalize default recording device^M
    if (!BASS_RecordInit(-1)) {
        printf("Can't initialize recording device");
        return;
    }
    // initialize default output device^M
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        printf("Can't initialize output device");
    }
    output = BASS_StreamCreate(44100, 1, 0, STREAMPROC_PUSH, 0);
    BASS_INFO info;
    BASS_GetInfo(&info);
    prebuf = BASS_ChannelSeconds2Bytes(output, info.minbuf / 1000.0);
    printf("%d\n", prebuf);
    input = BASS_RecordStart(4410, 1, MAKELONG(0, 10), RecordProc, 0);

}


