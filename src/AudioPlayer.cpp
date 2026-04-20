//
// Created by yevhenii on 20.04.2026.
//
#include "AudioPlayer.h"
#include "Arpeggiator.h"
#include <iostream>
#include <utility>

#define MINIAUDIO_IMPLEMENTATION
#include "../vendor/miniaudio.h"

namespace AudioEngine {
    AudioPlayer::AudioPlayer(float sample_rate, Source source) : sample_rate(sample_rate), source(std::move(source)) {
    }

    void AudioPlayer::play() {
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
        config.playback.format = ma_format_f32;
        config.playback.channels = 2;
        config.sampleRate = static_cast<ma_uint32>(this->sample_rate);
        config.dataCallback = data_callback;
        config.pUserData = &this->source;

        ma_device device;
        ma_device_init(nullptr, &config, &device);
        ma_device_start(&device);

        std::cin.get();

        ma_device_uninit(&device);
    }

    void AudioPlayer::data_callback(ma_device *device, void *output, const void *input,
                                    const ma_uint32 frameCount) {
        auto *source = static_cast<AudioPlayer::Source *>(device->pUserData);
        auto *out = static_cast<float *>(output);

        for (ma_uint32 i = 0; i < frameCount; i++) {
            const float sample = std::visit([](auto &s) {
                return static_cast<float>(s.next_sample());
            }, *source);

            out[i * 2 + 0] = sample;
            out[i * 2 + 1] = sample;
        }
    }
};
