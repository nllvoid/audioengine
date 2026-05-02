//
// Created by yevhenii on 20.04.2026.
//
#include "AudioEffect.h"

#ifndef SOFTCLIPPING_H
#define SOFTCLIPPING_H

namespace AudioEngine {
    class SoftClipping final : public AudioEngine::AudioEffect {
    public:
        explicit SoftClipping(double drive);

        double process(double sample) override;

    private:
        double drive{};
    };
}
#endif //SOFTCLIPPING_H
