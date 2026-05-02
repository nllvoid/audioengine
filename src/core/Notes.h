//
// Created by yevhenii on 20.04.2026.
//

#ifndef NOTES_H
#define NOTES_H

namespace AudioEngine {
    enum class Pitch { C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B };

    enum class Octave { O0, O1, O2, O3, O4, O5, O6, O7, O8 };

    constexpr float pitch_frequencies[12] = {
        261.63f, 277.18f, 293.66f, 311.13f,
        329.63f, 349.23f, 369.99f, 392.00f,
        415.30f, 440.00f, 466.16f, 493.88f
    };

    constexpr float octave_multipliers[9] = {
        1.0f / 16.0f, 1.0f / 8.0f, 1.0f / 4.0f, 1.0f / 2.0f,
        1.0f, 2.0f, 4.0f, 8.0f, 16.0f
    };

    class Note {
    public:
        Pitch pitch;
        Octave octave;

        constexpr Note() : pitch(Pitch::A), octave(Octave::O4) {
        }

        constexpr Note(const Pitch pitch, const Octave octave) : pitch(pitch), octave(octave) {
        }

        [[nodiscard]] constexpr float frequency() const {
            return pitch_frequencies[static_cast<int>(pitch)]
                   * octave_multipliers[static_cast<int>(octave)];
        }

        [[nodiscard]] std::size_t duration_samples(float sample_rate) const {
            return static_cast<std::size_t>(sample_rate / 4.f);
        }
    };
}

#endif //NOTES_H
