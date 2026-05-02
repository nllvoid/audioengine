//
// Created by yevhenii on 02.05.2026.
//
#include <vector>

#ifndef HEADER_H
#define HEADER_H


namespace AudioEngine {
    constexpr std::array<std::byte, 4> HEADER_IDENTIFIER = {
        std::byte{0x4D}, std::byte{0x54}, std::byte{0x68}, std::byte{0x64}
    }; // MThd
    // The first 14 bytes of the sample file
    class Header {
    public:
        static Header parse_file_header(const std::vector<std::byte> &file);

        static bool is_file_contains_header(const std::vector<std::byte> &file);

        std::uint32_t chunk_len{};
        std::uint16_t format{};
        std::uint16_t tracks_number{};
        std::uint16_t ticks_division{};
    };

    void print_header(const AudioEngine::Header &header);
}

#endif //HEADER_H
