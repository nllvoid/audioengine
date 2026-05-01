//
// Created by yevhenii on 20.04.2026.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <memory>
#include <memory>
#include <vector>

#include "../effects/AudioEffect.h"
#include "Envelope.h"
#include "../effects/IEffectChain.h"
#include "../effects/LowPassFilter.h"

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
        Oscillator(float sample_rate, uint8_t amplitude, float frequency, WaveType wave);

        Oscillator(float sample_rate, uint8_t amplitude, float frequency, WaveType wave,
                   PitchModulation modulation, float target_frequency);

        Oscillator(float sample_rate, uint8_t amplitude, float frequency, WaveType wave,
                   PitchModulation modulation, float target_frequency, float glide_rate);

        Oscillator(float sample_rate, uint8_t amplitude, float frequency, WaveType wave,
                   PitchModulation modulation, float target_frequency, float glide_rate,
                   float lfo_phase, float lfo_frequency, float lfo_depth);

        double next_sample();

        void set_frequency(float frequency);

        void set_target_frequency(float frequency);

        [[nodiscard]] float get_frequency() const;

        void set_effect_chain(IEffectChain& chain);

        void set_envelope(Envelope& envelope);

        void note_on() const;


    private:
        float sample_rate{};
        float frequency{};
        float phase = 0.f;
        uint8_t amplitude{};
        WaveType wave;

        PitchModulation modulation{};

        float target_frequency{};
        float glide_rate{};

        float lfo_phase{};
        float lfo_frequency{};
        float lfo_depth{};

        AudioEngine::IEffectChain* effect_chain = nullptr;
        AudioEngine::Envelope* envelope = nullptr;

        void update_phase();

        void apply_linear();

        void apply_exponential();

        void apply_logarithmic();

        void apply_LFO();
    };
}

#endif //OSCILLATOR_H
