//
// Created by yevhenii on 20.04.2026.
//
#include "HardClipping.h"
#include <algorithm>

namespace AudioEngine {
    HardClipping::HardClipping(const double threshold) : threshold(threshold) {
    }

    double HardClipping::process(const double sample) {
        return std::clamp(sample, -this->threshold, this->threshold);
    }
}
