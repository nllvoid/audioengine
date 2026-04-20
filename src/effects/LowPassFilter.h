//
// Created by yevhenii on 20.04.2026.
//

#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include "../AudioEffect.h"

namespace AudioEngine {
    class LowPassFilter final : public AudioEngine::AudioEffect {
    public:
        LowPassFilter(float cutoff, float sample_rate);

        double process(double sample) override;

    private:
        float cutoff{};
        float sample_rate{};
        float alpha{};
        double prev{};
    };
}
#endif //LOWPASSFILTER_H
