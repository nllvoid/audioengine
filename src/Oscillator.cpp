//
// Created by yevhenii on 20.04.2026.
//
#include "Oscillator.h"
#include <cmath>
#include <print>

namespace AudioEngine {
    Oscillator::Oscillator(float const sample_rate, float const frequency, WaveType const wave)
        : sample_rate(sample_rate), frequency(frequency), wave(wave) {
    }

    Oscillator::Oscillator(float const sample_rate, float const frequency, WaveType const wave,
                           PitchModulation const modulation, float const target_frequency)
        : sample_rate(sample_rate), frequency(frequency), wave(wave), modulation(modulation),
          target_frequency(target_frequency) {
    }

    Oscillator::Oscillator(float const sample_rate, float const frequency, WaveType const wave,
                           PitchModulation const modulation, float const target_frequency, float const glide_rate)
        : sample_rate(sample_rate), frequency(frequency), wave(wave), modulation(modulation),
          target_frequency(target_frequency), glide_rate(glide_rate) {
    }

    Oscillator::Oscillator(float const sample_rate, float const frequency, WaveType const wave,
                           PitchModulation const modulation, float const target_frequency, float const glide_rate,
                           float const lfo_phase, float const lfo_frequency, float const lfo_depth)
        : sample_rate(sample_rate), frequency(frequency), wave(wave), modulation(modulation),
          target_frequency(target_frequency), glide_rate(glide_rate), lfo_phase(lfo_phase),
          lfo_frequency(lfo_frequency), lfo_depth(lfo_depth) {
    }

    double Oscillator::next_sample() {
        switch (this->modulation) {
            case PitchModulation::LINEAR: apply_linear();
                break;
            case PitchModulation::EXPONENTIAL: apply_exponential();
                break;
            case PitchModulation::LOGARITHMIC: apply_logarithmic();
                break;
            case PitchModulation::LFO: apply_LFO();
                break;
            case PitchModulation::NONE: break;
        }

        double value = 0;
        switch (wave) {
            case WaveType::SINE: value = std::sin(2.0 * M_PI * phase);
                break;
            case WaveType::SQUARE: value = phase < 0.5 ? 1.0 : -1.0;
                break;
            case WaveType::SAW: value = 2.0 * phase - 1.0;
                break;
            case WaveType::TRIANGLE: value = phase < 0.5 ? (4.0 * phase - 1.0) : (3.0 - 4.0 * phase);
                break;
        }
        update_phase();
        return value;
    }

    void Oscillator::set_frequency(const float frequency) {
        this->frequency = frequency;
    }

    float Oscillator::get_frequency() const {
        return this->frequency;
    }

    void Oscillator::update_phase() {
        this->phase = std::fmod(this->phase + this->frequency / this->sample_rate, 1.0f);
    }

    void Oscillator::apply_linear() {
        this->frequency += (this->target_frequency - this->frequency) * this->glide_rate;
        std::printf("%f ", frequency);
    }

    void Oscillator::apply_exponential() {
        this->frequency *= std::pow(this->target_frequency / this->frequency, this->glide_rate);
    }

    void Oscillator::apply_logarithmic() {
        const float diff = this->target_frequency - this->frequency;
        this->frequency += diff * this->glide_rate * (1.0f + std::log(1.0f + std::abs(diff)));
    }

    void Oscillator::apply_LFO() {
        this->frequency = this->target_frequency + static_cast<float>(
                              std::sin(2.0 * M_PI * this->lfo_phase) * this->lfo_depth);
        this->lfo_phase = std::fmod(this->lfo_phase + this->lfo_frequency / this->sample_rate, 1.0f);
        std::printf("%f ", frequency);
    }
}
