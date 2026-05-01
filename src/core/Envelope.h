//
// Created by yevhenii on 01.05.2026.
//

#ifndef ENVELOPE_H
#define ENVELOPE_H
namespace AudioEngine {
    class Envelope {
    public:
        enum class Stage { IDLE, ATTACK, DECAY, SUSTAIN, RELEASE };

        Envelope(float sample_rate, float attack, float decay, float sustain, float release);

        void note_on();
        void note_off();

        float next();
        [[nodiscard]] bool is_idle() const;

    private:
        float sample_rate;
        float attack;
        float decay;
        float sustain;
        float release;
        float current_level = 0.f;
        Stage stage = Stage::IDLE;
    };
}
#endif //ENVELOPE_H
