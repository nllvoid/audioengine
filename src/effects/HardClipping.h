//
// Created by yevhenii on 20.04.2026.
//
#include "AudioEffect.h"

#ifndef HARDCLIPPING_H
#define HARDCLIPPING_H

namespace AudioEngine {
    class HardClipping final : public AudioEngine::AudioEffect {
    public:
        explicit HardClipping(double threshold);

        double process(double sample) override;

    private:
        double threshold{};
    };
}
#endif //HARDCLIPPING_H
