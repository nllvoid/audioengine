//
// Created by yevhenii on 20.04.2026.
//
#include "Arpeggiator.h"

#include <utility>

namespace AudioEngine {
    Arpeggiator::Arpeggiator(std::vector<float> notes, const float rate, const float sample_rate,
                             AudioEngine::Oscillator oscillator)
        : oscillator(std::move(oscillator)),
          notes(std::move(notes)),
          step_size(static_cast<size_t>(sample_rate / rate)) {
        this->oscillator.set_target_frequency(this->notes[0]);
    }

    double Arpeggiator::next_sample() {
        if (++this->counter >= this->step_size) {
            this->counter = 0;
            this->current_index = (this->current_index + 1) % this->notes.size();
            this->oscillator.set_target_frequency(this->notes[this->current_index]);
        }
        return this->oscillator.next_sample();
    }
}
