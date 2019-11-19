//
// Created by kira on 10.11.2019.
//

#include <alsa/asoundlib.h>

#include "capture.h"

#define SOUNDCARD "default"

alsa::Capture::Capture() : capture_handle(), err(0) {
    snd_pcm_hw_params_t *hw_params;
    unsigned rate = 44100;

    if ((err = snd_pcm_open (&capture_handle, SOUNDCARD, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n", SOUNDCARD, snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n", snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n", snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n", snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n", snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n", snd_strerror (err));
    }

    snd_pcm_hw_params_free (hw_params);

    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror (err));
    }
}


alsa::Capture::~Capture() {
    snd_pcm_close (capture_handle);
}


uint32_t alsa::Capture::get_sample(void *buf, size_t sample_size) {
    if ((err = snd_pcm_readi(capture_handle, buf, sample_size)) != sample_size) {
        fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror(err));
    }

    return err;
}
