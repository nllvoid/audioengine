//
// Created by yevhenii on 02.05.2026.
//
#include <algorithm>

#include "core/Notes.h"

#ifndef MIDINOTE_H
#define MIDINOTE_H

namespace AudioEngine {
    struct MidiNote {
        AudioEngine::Note note;
        std::uint32_t tick_on;
        std::uint32_t tick_off;
        std::uint8_t velocity;
        std::uint8_t channel;
        float ticks_per_sample{};

        [[nodiscard]] std::uint32_t duration_ticks() const { return tick_off - tick_on; }

        [[nodiscard]] size_t duration_samples(float sample_rate) const {
            if (ticks_per_sample <= 0.f) return 22050;
            return static_cast<std::size_t>(duration_ticks() / ticks_per_sample);
        }
    };

    inline AudioEngine::Note midi_note_to_note(const std::uint8_t midi) {
        const auto pitch = static_cast<AudioEngine::Pitch>(midi % 12);
        const auto octave = static_cast<AudioEngine::Octave>(std::clamp(midi / 12 - 1, 0, 8));
        return AudioEngine::Note(pitch, octave);
    }
}
#endif // MIDINOTE_H
