//
// Created by yevhenii on 20.04.2026.
//
#include "Delay.h"

namespace AudioEngine {
    Delay::Delay(const int delaySamples, const double feedback, const double mix)
        : buffer(delaySamples, 0.0),
          delaySamples(delaySamples),
          feedback(feedback),
          mix(mix) {
    }

    double Delay::process(const double sample) {
        const size_t readHead = (this->writeHead - this->delaySamples + this->buffer.size()) % this->buffer.size();
        const double delayed = this->buffer[readHead];

        this->buffer[this->writeHead] = sample + delayed * this->feedback;
        this->writeHead = (this->writeHead + 1) % this->buffer.size();

        return sample * (1.0 - this->mix) + delayed * this->mix;
    }
}
