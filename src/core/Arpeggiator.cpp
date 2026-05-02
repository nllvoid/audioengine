//
// Created by yevhenii on 20.04.2026.
//
#include "Arpeggiator.h"

namespace AudioEngine {
    void Arpeggiator::advance_note() {
        const auto &e = this->entries.at(this->current_index);
        this->oscillator.set_target_note(e.note);
        this->oscillator.note_on();
    }

    double Arpeggiator::next_sample() {
        if (this->entries.empty()) return 0.0;

        if (++this->counter >= this->entries.at(this->current_index).step_size) {
            this->counter = 0;
            this->oscillator.note_off();
            this->current_index = (this->current_index + 1) % this->entries.size();
            advance_note();
        }
        return this->oscillator.next_sample();
    }

    AudioEngine::Oscillator &Arpeggiator::get_oscillator() { return this->oscillator; }
}
