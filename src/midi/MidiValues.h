//
// Created by yevhenii on 02.05.2026.
//
#include <vector>

#ifndef MIDIVALUES_H
#define MIDIVALUES_H

namespace AudioEngine {
    std::uint32_t parse_tempo(const std::vector<std::byte> &file, std::size_t offset);

    float get_bpm(float tempo_us);

    float get_rate(float bpm);
}
#endif //MIDIVALUES_H
