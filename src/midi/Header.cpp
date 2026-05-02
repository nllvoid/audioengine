//
// Created by yevhenii on 02.05.2026.
//
#include "Header.h"


namespace AudioEngine {
    Header Header::parse_file_header(const std::vector<std::byte> &file) {
        if (file.size() < HEADER_IDENTIFIER.size() + sizeof(Header))
            throw std::runtime_error("MIDI file is too small!");
        if (!is_file_contains_header(file))
            throw std::runtime_error("MIDI file have no header inside!");

        Header header;
        std::memcpy(&header, file.data() + HEADER_IDENTIFIER.size(), sizeof(Header));

        header.chunk_len = __builtin_bswap32(header.chunk_len);
        header.format = __builtin_bswap16(header.format);
        header.tracks_number = __builtin_bswap16(header.tracks_number);
        header.ticks_division = __builtin_bswap16(header.ticks_division);
        return header;
    }

    bool Header::is_file_contains_header(const std::vector<std::byte> &file) {
        if (file.size() < HEADER_IDENTIFIER.size()) return false;
        return std::equal(HEADER_IDENTIFIER.begin(), HEADER_IDENTIFIER.end(), file.begin());
    }

    void print_header(const Header &header) {
        std::printf("chunk_len:      0x%08X (%u)\n", header.chunk_len, header.chunk_len);
        std::printf("format:         0x%04X (%u)\n", header.format, header.format);
        std::printf("tracks_number:  0x%04X (%u)\n", header.tracks_number, header.tracks_number);
        std::printf("ticks_division: 0x%04X (%u)\n", header.ticks_division, header.ticks_division);
    }
}
