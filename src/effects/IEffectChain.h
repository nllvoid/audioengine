//
// Created by yevhenii on 01.05.2026.
//

#ifndef IEFFECTCHAIN_H
#define IEFFECTCHAIN_H

namespace AudioEngine {
    class IEffectChain {
    public:
        virtual double process(double &sample) = 0;

        virtual ~IEffectChain() = default;

    };
}

#endif //IEFFECTCHAIN_H
