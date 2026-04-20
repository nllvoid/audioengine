//
// Created by yevhenii on 20.04.2026.
//

#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H
#include <vector>

#include "Oscillator.h"

namespace AudioEngine {
    class Arpeggiator {
    public:
        Arpeggiator(std::vector<float> notes, float rate, float sample_rate, AudioEngine::Oscillator oscillator);

        double next_sample();

    private:
        AudioEngine::Oscillator oscillator;
        std::vector<float> notes;
        size_t current_index{};
        size_t counter{};
        size_t step_size{};
    };
}
#endif //ARPEGGIATOR_H
