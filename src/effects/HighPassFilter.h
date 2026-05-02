//
// Created by yevhenii on 20.04.2026.
//
#include "AudioEffect.h"

#ifndef HIGHPASSFILTER_H
#define HIGHPASSFILTER_H

namespace AudioEngine {
    class HighPassFilter final : public AudioEngine::AudioEffect {
    public:
        HighPassFilter(float cutoff, float sample_rate);

        double process(double sample) override;

    private:
        float cutoff{};
        float sample_rate{};
        float alpha{};
        double prev_input{};
        double prev_output{};
    };
}
#endif //HIGHPASSFILTER_H
