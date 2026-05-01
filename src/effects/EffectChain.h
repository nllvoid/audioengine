//
// Created by yevhenii on 01.05.2026.
//

#ifndef EFFECTCHAIN_H
#define EFFECTCHAIN_H
#include <algorithm>

#include "IEffectChain.h"

namespace AudioEngine {
    template<typename... Effects>
    class EffectChain final : public IEffectChain {
    public:
        explicit EffectChain(Effects... effects) : effects(std::move(effects)...) {}

        void process(float& sample) override {
            std::apply([&](auto&... e) {
                (e.process(sample), ...);
            }, effects);
        }
    private:
        std::tuple<Effects...> effects{};
    };
}

#endif //EFFECTCHAIN_H
