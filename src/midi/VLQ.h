//
// Created by yevhenii on 02.05.2026.
//
#include <vector>

#ifndef VLQ_H
#define VLQ_H

namespace AudioEngine {
    std::uint32_t read_vlq(const std::vector<std::byte> &data, std::size_t &pos);
}
#endif //VLQ_H
