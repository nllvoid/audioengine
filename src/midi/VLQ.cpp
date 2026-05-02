//
// Created by yevhenii on 02.05.2026.
//
#include <vector>

namespace AudioEngine {
    std::uint32_t read_vlq(const std::vector<std::byte> &data, std::size_t &pos) {
        std::uint32_t value = 0;
        std::uint8_t byte;
        do {
            byte = std::to_integer<std::uint8_t>(data[pos++]);
            value = value << 7 | byte & 0x7F;
        } while (byte & 0x80);
        return value;
    }
}
