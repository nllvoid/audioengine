//
// Created by yevhenii on 02.05.2026.
//
#include "MidiNote.h"
#include <array>
#include <cstdint>
#include <cstddef>
#include <vector>

#ifndef TRACKHEADER_H
#define TRACKHEADER_H

namespace AudioEngine {
    struct TrackHeader {
        std::array<std::byte, 4> identifier; // MTrk
        uint32_t length;
    };

    std::vector<AudioEngine::MidiNote> parse_track(const std::vector<std::byte> &file,
                                                   std::size_t offset,
                                                   float ticks_per_sample);
}

#endif //TRACKHEADER_H
