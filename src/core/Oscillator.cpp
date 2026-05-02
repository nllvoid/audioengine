//
// Created by yevhenii on 20.04.2026.
//
#include "Oscillator.h"
#include "../effects/IEffectChain.h"
#include "Envelope.h"
#include "Notes.h"

namespace AudioEngine {
    Oscillator::Oscillator(float const sample_rate, std::uint8_t const amplitude, Note const note, WaveType const wave)
        : sample_rate(sample_rate), note(note), current_frequency(note.frequency()), amplitude(amplitude), wave(wave),
          target_note(note) {
    }

    Oscillator::Oscillator(float const sample_rate, std::uint8_t const amplitude, Note const note, WaveType const wave,
                           PitchModulation const modulation, Note const target_note)
        : sample_rate(sample_rate), note(note), current_frequency(note.frequency()), amplitude(amplitude), wave(wave),
          modulation(modulation), target_note(target_note) {
    }

    Oscillator::Oscillator(float const sample_rate, std::uint8_t const amplitude, Note const note, WaveType const wave,
                           PitchModulation const modulation, Note const target_note, float const glide_rate)
        : sample_rate(sample_rate), note(note), current_frequency(note.frequency()), amplitude(amplitude), wave(wave),
          modulation(modulation), target_note(target_note), glide_rate(glide_rate) {
    }

    Oscillator::Oscillator(float const sample_rate, std::uint8_t const amplitude, Note const note, WaveType const wave,
                           PitchModulation const modulation, Note const target_note, float const glide_rate,
                           float const lfo_phase, float const lfo_frequency, float const lfo_depth)
        : sample_rate(sample_rate), note(note), current_frequency(note.frequency()), amplitude(amplitude), wave(wave),
          modulation(modulation), target_note(target_note), glide_rate(glide_rate),
          lfo_phase(lfo_phase), lfo_frequency(lfo_frequency), lfo_depth(lfo_depth) {
    }

    double Oscillator::next_sample() {
        switch (this->modulation) {
            case PitchModulation::LINEAR:      this->apply_linear();      break;
            case PitchModulation::EXPONENTIAL: this->apply_exponential(); break;
            case PitchModulation::LOGARITHMIC: this->apply_logarithmic(); break;
            case PitchModulation::LFO:         this->apply_LFO();         break;
        }

        const double freq = this->current_frequency;
        const double dt   = freq / this->sample_rate;
        const double p    = this->phase;

        double value = 0.0;
        switch (this->wave) {
            case WaveType::SINE:
                value = this->amplitude * std::sin(2.0 * M_PI * p);
                break;

            case WaveType::SQUARE: {
                value = p < 0.5 ? 1.0 : -1.0;
                value += polyblep(p, dt);
                value -= polyblep(std::fmod(p + 0.5, 1.0), dt);
                value *= this->amplitude;
                break;
            }

            case WaveType::SAW: {
                value = 2.0 * p - 1.0;
                value -= polyblep(p, dt);
                value *= this->amplitude;
                break;
            }

            case WaveType::TRIANGLE: {
                double square = p < 0.5 ? 1.0 : -1.0;
                square += polyblep(p, dt);
                square -= polyblep(std::fmod(p + 0.5, 1.0), dt);
                this->tri_accumulator = dt * 4.0 * square + (1.0 - dt) * this->tri_accumulator;
                value = this->amplitude * this->tri_accumulator;
                break;
            }
        }

        if (effect_chain) {
            auto f = value;
            effect_chain->process(f);
            value = f;
        }

        if (envelope) value *= envelope->next();

        this->phase = std::fmod(p + dt, 1.0);
        return value;
    }

    void Oscillator::set_note(const AudioEngine::Note note) {
        this->note = note;
        this->current_frequency = note.frequency();
    }

    void Oscillator::set_target_note(const AudioEngine::Note note) {
        this->target_note = note;
    }

    float Oscillator::get_frequency() const {
        return this->current_frequency;
    }

    void Oscillator::set_effect_chain(AudioEngine::IEffectChain &chain) {
        this->effect_chain = &chain;
    }

    void Oscillator::set_envelope(AudioEngine::Envelope &envelope) {
        this->envelope = &envelope;
    }

    void Oscillator::note_on() const {
        if (envelope) envelope->note_on();
    }

    void Oscillator::note_off() const {
        if (envelope) envelope->note_off();
    }

    void Oscillator::apply_linear() {
        const float target = this->target_note.frequency();
        this->current_frequency += (target - this->current_frequency) * this->glide_rate;
    }

    void Oscillator::apply_exponential() {
        const float target = this->target_note.frequency();
        this->current_frequency *= std::pow(target / this->current_frequency, this->glide_rate);
    }

    void Oscillator::apply_logarithmic() {
        const float target = this->target_note.frequency();
        const float diff = target - this->current_frequency;
        this->current_frequency += diff * this->glide_rate * (1.0f + std::log(1.0f + std::abs(diff)));
    }

    void Oscillator::apply_LFO() {
        this->current_frequency = this->note.frequency() + static_cast<float>(
                                      std::sin(2.0 * M_PI * this->lfo_phase) * this->lfo_depth);
        this->lfo_phase = std::fmod(this->lfo_phase + this->lfo_frequency / this->sample_rate, 1.0f);
    }

    double Oscillator::polyblep(double t, double dt) const {
        if (t < dt) {
            t /= dt;
            return t + t - t * t - 1.0;
        }
        if (t > 1.0 - dt) {
            t = (t - 1.0) / dt;
            return t * t + t + t + 1.0;
        }
        return 0.0;
    }
}
