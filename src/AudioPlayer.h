//
// Created by yevhenii on 20.04.2026.
//

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "Arpeggiator.h"
#include "Oscillator.h"
#include "../vendor/miniaudio.h"

namespace AudioEngine {
    class AudioPlayer {
    public:
        using Source = std::variant<Oscillator, Arpeggiator>;

        AudioPlayer(float sample_rate, Source source);

        void play();

    private:
        static void data_callback(ma_device *device, void *output, const void *input, ma_uint32 frameCount);

        Source source;
        float sample_rate;
    };
}

#endif //AUDIOPLAYER_H
