//
// Created by yevhenii on 20.04.2026.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <memory>
#include <memory>
#include <vector>

#include "AudioEffect.h"
#include "effects/LowPassFilter.h"

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
        Oscillator(float sample_rate, float frequency, WaveType wave);

        Oscillator(float sample_rate, float frequency, WaveType wave,
                   PitchModulation modulation, float target_frequency);

        Oscillator(float sample_rate, float frequency, WaveType wave,
                   PitchModulation modulation, float target_frequency, float glide_rate);

        Oscillator(float sample_rate, float frequency, WaveType wave,
                   PitchModulation modulation, float target_frequency, float glide_rate,
                   float lfo_phase, float lfo_frequency, float lfo_depth);

        double next_sample();

        void set_frequency(float frequency);

        [[nodiscard]] float get_frequency() const;

        void add_effect(std::unique_ptr<AudioEffect> effect);
    private:
        float sample_rate{};
        float frequency{};
        float phase = 0.f;
        WaveType wave;

        PitchModulation modulation{};

        float target_frequency{};
        float glide_rate{};

        float lfo_phase{};
        float lfo_frequency{};
        float lfo_depth{};

        std::vector<std::unique_ptr<AudioEffect> > effects;

        void update_phase();

        void apply_linear();

        void apply_exponential();

        void apply_logarithmic();

        void apply_LFO();
    };
}

#endif //OSCILLATOR_H
