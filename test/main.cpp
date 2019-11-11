//
// Created by antonrampage on 11.11.2019.
//
#include "list_devices.hpp"

int main(int argc, char *argv[]) {
    int ctr;

    // This is where we'll store the input device list
    auto pa_input_devicelist = (pa_devicelist_t *)calloc(16, sizeof(pa_devicelist_t));

    // This is where we'll store the output device list
    auto pa_output_devicelist = (pa_devicelist_t *)calloc(16, sizeof(pa_devicelist_t));

    if (pa_get_devicelist(pa_input_devicelist, pa_output_devicelist) < 0) {
        fprintf(stderr, "failed to get device list\n");
        return 1;
    }

    for (ctr = 0; ctr < 16; ctr++) {
        if (! pa_output_devicelist[ctr].initialized) {
            break;
        }
        printf("=======[ Output Device #%d ]=======\n", ctr+1);
        printf("Description: %s\n", pa_output_devicelist[ctr].description);
        printf("Name: %s\n", pa_output_devicelist[ctr].name);
        printf("Index: %d\n", pa_output_devicelist[ctr].index);
        printf("\n");
    }

    for (ctr = 0; ctr < 16; ctr++) {
        if (! pa_input_devicelist[ctr].initialized) {
            break;
        }
        printf("=======[ Input Device #%d ]=======\n", ctr+1);
        printf("Description: %s\n", pa_input_devicelist[ctr].description);
        printf("Name: %s\n", pa_input_devicelist[ctr].name);
        printf("Index: %d\n", pa_input_devicelist[ctr].index);
        printf("\n");
    }
    return 0;
}
