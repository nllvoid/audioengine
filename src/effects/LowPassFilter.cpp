//
// Created by yevhenii on 20.04.2026.
//
#include "LowPassFilter.h"
#include <cmath>

namespace AudioEngine {
    LowPassFilter::LowPassFilter(const float cutoff, const float sample_rate) : cutoff(cutoff),
        sample_rate(sample_rate) {
        this->alpha = 1.f - static_cast<float>(std::exp(-2.f * M_PI * this->cutoff / this->sample_rate));
    }

    double LowPassFilter::process(const double sample) {
        this->prev = this->prev + this->alpha * (sample - this->prev);
        return this->prev;
    }
}
