//
// Created by yevhenii on 20.04.2026.
//
#include <vector>

#include "AudioEffect.h"

#ifndef DELAY_H
#define DELAY_H


namespace AudioEngine {
    class Delay final : public AudioEngine::AudioEffect {
    public:
        Delay(int delaySamples, double feedback, double mix);

        double process(double sample) override;

    private:
        std::vector<double> buffer;
        size_t writeHead{};
        size_t delaySamples{};
        double feedback{};
        double mix{};
    };
}
#endif //DELAY_H
