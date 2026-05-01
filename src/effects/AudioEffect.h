//
// Created by yevhenii on 20.04.2026.
//

#ifndef AUDIOEFFECT_H
#define AUDIOEFFECT_H

namespace AudioEngine {
    class AudioEffect {
    public:
        virtual ~AudioEffect() = default;

        virtual double process(double sample) = 0;
    };
}

#endif //AUDIOEFFECT_H
