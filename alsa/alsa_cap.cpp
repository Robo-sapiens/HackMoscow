#include <alsa/asoundlib.h>
#include <iostream>

int main (int argc, char **argv) {
    int err = 0;
    int16_t buf[1024];
    snd_pcm_t *capture_handle;
    snd_pcm_hw_params_t *hw_params;
    unsigned rate = 44100;

    if ((err = snd_pcm_open (&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n",
                 "default",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    snd_pcm_hw_params_free (hw_params);

    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    for (int i = 0; i < 100000000; ++i) {
        if ((err = snd_pcm_readi (capture_handle, buf, 1024)) != 1024) {
            fprintf (stderr, "read from audio interface failed (%s)\n",
                     snd_strerror (err));
            exit (1);
        }
        int16_t max = 0;
        int16_t min = 0;
        for (int16_t j : buf) {
            max = std::max(j, max);
            min = std::min(j, min);
        }
        std::cout << max << ' ' << min << std::endl;
    }


    snd_pcm_close (capture_handle);
    exit (0);
}