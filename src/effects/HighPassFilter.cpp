//
// Created by yevhenii on 20.04.2026.
//
#include "HighPassFilter.h"

#include <math.h>

namespace AudioEngine {
    HighPassFilter::HighPassFilter(const float cutoff, const float sample_rate)
        : cutoff(cutoff), sample_rate(sample_rate) {
        this->alpha = 1.f / static_cast<float>(1.f + 2.f * M_PI * this->cutoff / this->sample_rate);
    }

    double HighPassFilter::process(const double sample) {
        this->prev_output = this->alpha * (this->prev_output + sample - this->prev_input);
        this->prev_input = sample;
        return this->prev_output;
    }
}
