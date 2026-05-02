//
// Created by yevhenii on 01.05.2026.
//
#include "Envelope.h"

namespace AudioEngine {
    Envelope::Envelope(const float sample_rate, const float attack, const float decay, const float sustain,
                       const float release)
        : sample_rate(sample_rate), attack(attack), decay(decay),
          sustain(sustain), release(release) {
    }

    void Envelope::note_on() { this->current_level = 0.f; this->stage = Stage::ATTACK; }
    void Envelope::note_off() { this->stage = Stage::RELEASE; }

    float Envelope::next() {
        switch (this->stage) {
            case Stage::ATTACK:
                this->current_level += 1.f / (this->attack * this->sample_rate);
                if (this->current_level >= 1.f) {
                    this->current_level = 1.f;
                    this->stage = Stage::DECAY;
                }
                break;
            case Stage::DECAY:
                this->current_level -= (1.f - this->sustain) / (this->decay * this->sample_rate);
                if (this->current_level <= this->sustain) {
                    this->current_level = this->sustain;
                    this->stage = Stage::SUSTAIN;
                }
                break;
            case Stage::SUSTAIN:
                this->current_level = this->sustain;
                break;
            case Stage::RELEASE:
                if (this->sustain <= 0.f) {
                    this->current_level = 0.f;
                    this->stage = Stage::IDLE;
                    break;
                }
                this->current_level -= this->sustain / (this->release * this->sample_rate);
                if (this->current_level <= 0.f) {
                    this->current_level = 0.f;
                    this->stage = Stage::IDLE;
                }
                break;
            case Stage::IDLE:
                this->current_level = 0.f;
                break;
        }
        return this->current_level;
    }

    [[nodiscard]] bool Envelope::is_idle() const { return this->stage == Stage::IDLE; }
}
