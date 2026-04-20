//
// Created by yevhenii on 20.04.2026.
//
#include "SoftClipping.h"
#include <algorithm>

namespace AudioEngine {
    SoftClipping::SoftClipping(const double drive) : drive(drive) {
    }
    double SoftClipping::process(const double sample) {
        return std::tanh(sample * drive) / std::tanh(drive);
    }
}