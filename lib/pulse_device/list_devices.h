#ifndef __LIST_DEVICES_LIB_H__
#define __LIST_DEVICES_LIB_H__

#include <iostream>
#include <cstring>
#include <pulse/pulseaudio.h>
#include <vector>

typedef struct pa_devicelist {
    uint8_t initialized;
    char name[512];
    uint32_t index;
    char description[256];
} pa_devicelist_t;

int pa_get_devicelist(pa_devicelist_t *input, pa_devicelist_t *output);

#endif

