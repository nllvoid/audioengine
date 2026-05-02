//
// Created by yevhenii on 02.05.2026.
//

#ifndef REVERB_H
#define REVERB_H
#include <array>
#include <vector>
#include "AudioEffect.h"

namespace AudioEngine {
    class Reverb : public AudioEffect {
    public:
        Reverb(float sample_rate, float room_size = 0.8f, float damping = 0.5f, float mix = 0.3f);
        double process(double sample) override;

    private:
        struct CombFilter {
            std::vector<float> buffer;
            int write_head{};
            float feedback{};
            float damp{};
            float last{};
            float process(float input);
        };

        struct AllpassFilter {
            std::vector<float> buffer;
            int write_head{};
            float feedback{0.5f};
            float process(float input);
        };

        std::array<CombFilter, 4> combs;
        std::array<AllpassFilter, 2> allpasses;
        float mix{};
    };
}
#endif //REVERB_H
