//
// Created by yevhenii on 01.05.2026.
//
#include <algorithm>

#include "IEffectChain.h"

#ifndef EFFECTCHAIN_H
#define EFFECTCHAIN_H


namespace AudioEngine {
    template<typename... Effects>
    class EffectChain final : public IEffectChain {
    public:
        explicit EffectChain(Effects... effects) : effects(std::move(effects)...) {
        }

        double process(double &sample) override {
            std::apply([&](auto &... e) {
                (void(sample = e.process(sample)), ...);
            }, effects);
            return sample;
        }

    private:
        std::tuple<Effects...> effects{};
    };
}

#endif //EFFECTCHAIN_H
