//
// Created by yevhenii on 20.04.2026.
//
#include <memory>

#include "Envelope.h"
#include "Notes.h"
#include "effects/IEffectChain.h"

#ifndef OSCILLATOR_H
#define OSCILLATOR_H


namespace AudioEngine {
    enum WaveType {
        SAW,
        SINE,
        SQUARE,
        TRIANGLE
    };

    enum PitchModulation {
        LINEAR,
        EXPONENTIAL,
        LOGARITHMIC,
        LFO
    };

    class Oscillator {
    public:
        Oscillator(float sample_rate, std::uint8_t amplitude, AudioEngine::Note note, WaveType wave);

        Oscillator(float sample_rate, std::uint8_t amplitude, AudioEngine::Note note, WaveType wave,
                   PitchModulation modulation, AudioEngine::Note target_note);

        Oscillator(float sample_rate, std::uint8_t amplitude, AudioEngine::Note note, WaveType wave,
                   PitchModulation modulation, AudioEngine::Note target_note, float glide_rate);

        Oscillator(float sample_rate, std::uint8_t amplitude, AudioEngine::Note note, WaveType wave,
                   PitchModulation modulation, AudioEngine::Note target_note, float glide_rate,
                   float lfo_phase, float lfo_frequency, float lfo_depth);

        double next_sample();

        void set_note(AudioEngine::Note);

        void set_target_note(AudioEngine::Note);

        [[nodiscard]] float get_frequency() const;

        void set_effect_chain(IEffectChain &chain);

        void set_envelope(Envelope &envelope);

        void note_on() const;

        void note_off() const;

    private:
        float sample_rate{};
        AudioEngine::Note note;
        float current_frequency = note.frequency();
        float phase = 0.f;
        std::uint8_t amplitude{};
        WaveType wave;

        PitchModulation modulation{};

        AudioEngine::Note target_note;
        float glide_rate{};

        float lfo_phase{};
        float lfo_frequency{};
        float lfo_depth{};

        AudioEngine::IEffectChain *effect_chain = nullptr;
        AudioEngine::Envelope *envelope = nullptr;
        double tri_accumulator{0.0};

        [[nodiscard]] double polyblep(double t, double dt) const;

        void update_phase();

        void apply_linear();

        void apply_exponential();

        void apply_logarithmic();

        void apply_LFO();
    };
}

#endif //OSCILLATOR_H
