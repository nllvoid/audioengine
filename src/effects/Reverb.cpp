//
// Created by yevhenii on 02.05.2026.
//
// Reverb.cpp
#include "Reverb.h"

namespace AudioEngine {
    float Reverb::CombFilter::process(float input) {
        float output = buffer[write_head];
        last = output * (1.f - damp) + last * damp;
        buffer[write_head] = input + last * feedback;
        write_head = (write_head + 1) % static_cast<int>(buffer.size());
        return output;
    }

    float Reverb::AllpassFilter::process(float input) {
        float output = buffer[write_head];
        buffer[write_head] = input + output * feedback;
        write_head = (write_head + 1) % static_cast<int>(buffer.size());
        return output - input;
    }

    Reverb::Reverb(float sample_rate, float room_size, float damping, float mix) : mix(mix) {
        const int delays[4] = {
            static_cast<int>(0.0297f * sample_rate),
            static_cast<int>(0.0371f * sample_rate),
            static_cast<int>(0.0411f * sample_rate),
            static_cast<int>(0.0437f * sample_rate)
        };
        for (int i = 0; i < 4; i++) {
            combs[i].buffer.resize(delays[i], 0.f);
            combs[i].feedback = room_size;
            combs[i].damp     = damping;
        }
        allpasses[0].buffer.resize(static_cast<int>(0.0090f * sample_rate), 0.f);
        allpasses[1].buffer.resize(static_cast<int>(0.0127f * sample_rate), 0.f);
    }

    double Reverb::process(double sample) {
        float input = static_cast<float>(sample);
        float wet   = 0.f;
        for (auto& c : combs)     wet += c.process(input);
        for (auto& a : allpasses) wet  = a.process(wet);
        return sample * (1.0 - mix) + wet * mix;
    }
}