//
// Created by yevhenii on 01.05.2026.
//
#include "Envelope.h"

namespace AudioEngine {
    Envelope::Envelope(const float sample_rate, const float attack, const float decay, const float sustain, const float release)
    : sample_rate(sample_rate), attack(attack), decay(decay),
      sustain(sustain), release(release) {}
    void Envelope::note_on()  { stage = Stage::ATTACK; }
    void Envelope::note_off() { stage = Stage::RELEASE; }
    float Envelope::next() {
        switch (stage) {
            case Stage::ATTACK:
                current_level += 1.f / (attack * sample_rate);
                if (current_level >= 1.f) {
                    current_level = 1.f;
                    stage = Stage::DECAY;
                }
                break;
            case Stage::DECAY:
                current_level -= (1.f - sustain) / (decay * sample_rate);
                if (current_level <= sustain) {
                    current_level = sustain;
                    stage = Stage::SUSTAIN;
                }
                break;
            case Stage::SUSTAIN:
                current_level = sustain;
                break;
            case Stage::RELEASE:
                current_level -= sustain / (release * sample_rate);
                if (current_level <= 0.f) {
                    current_level = 0.f;
                    stage = Stage::IDLE;
                }
                break;
            case Stage::IDLE:
                current_level = 0.f;
                break;
        }
        return current_level;
    }

    [[nodiscard]] bool Envelope::is_idle() const { return stage == Stage::IDLE; }

}