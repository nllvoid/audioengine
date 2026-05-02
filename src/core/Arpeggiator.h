//
// Created by yevhenii on 20.04.2026.
//
#include <vector>

#include "Oscillator.h"
#include "Notes.h"

#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

namespace AudioEngine {
    template<typename T>
    concept ArpNote = requires(T t, float sr)
    {
        { t.duration_samples(sr) } -> std::convertible_to<std::size_t>;
    } && (
        std::same_as<T, AudioEngine::Note>
        ||
        requires(T t) { { t.note } -> std::convertible_to<AudioEngine::Note>; }
    );

    class Arpeggiator {
    public:
        template<ArpNote T>
        Arpeggiator(std::vector<T> notes, float sample_rate, const AudioEngine::Oscillator &oscillator)
            : oscillator(oscillator) {
            for (const auto &n: notes) {
                AudioEngine::Note bare_note;
                if constexpr (std::same_as<T, AudioEngine::Note>) {
                    bare_note = n;
                } else {
                    bare_note = n.note;
                }
                entries.push_back({
                    bare_note,
                    std::max(n.duration_samples(sample_rate), std::size_t(1))
                });
            }
            advance_note();
        }

        AudioEngine::Oscillator &get_oscillator();

        double next_sample();

    private:
        struct Entry {
            AudioEngine::Note note;
            std::size_t step_size;
        };

        AudioEngine::Oscillator oscillator;
        std::vector<Entry> entries;
        std::size_t current_index{};
        std::size_t counter{};

        void advance_note();
    };
}
#endif // ARPEGGIATOR_H
