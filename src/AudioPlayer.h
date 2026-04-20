//
// Created by yevhenii on 20.04.2026.
//

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "Oscillator.h"
#include "../vendor/miniaudio.h"

namespace AudioEngine {

    class AudioPlayer {
    public:
        AudioPlayer(float sample_rate, AudioEngine::Oscillator oscillator);
        void play();
    private:
        static void data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);
        float sample_rate;
        AudioEngine::Oscillator oscillator;
    };
}

#endif //AUDIOPLAYER_H
