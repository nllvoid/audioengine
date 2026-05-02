//
// Created by yevhenii on 02.05.2026.
//
#include "MidiValues.h"

#include "TrackHeader.h"
#include "VLQ.h"


namespace AudioEngine {
    std::uint32_t parse_tempo(const std::vector<std::byte> &file, std::size_t offset) {
        AudioEngine::TrackHeader track_header;
        std::memcpy(&track_header, file.data() + offset, sizeof(AudioEngine::TrackHeader));
        track_header.length = __builtin_bswap32(track_header.length);
        offset += sizeof(AudioEngine::TrackHeader);

        std::size_t end = offset + track_header.length;
        while (offset < end) {
            read_vlq(file, offset);

            std::uint8_t status = std::to_integer<std::uint8_t>(file[offset++]);

            if (status == 0xFF) {
                std::uint8_t type = std::to_integer<std::uint8_t>(file[offset++]);
                std::uint32_t len = read_vlq(file, offset);

                if (type == 0x51 && len == 3) {
                    std::uint32_t tempo = (std::to_integer<std::uint32_t>(file[offset]) << 16) |
                                          (std::to_integer<std::uint32_t>(file[offset + 1]) << 8) |
                                          std::to_integer<std::uint32_t>(file[offset + 2]);
                    return tempo;
                }
                offset += len;
            } else if (status == 0xF0 || status == 0xF7) {
                offset += read_vlq(file, offset);
            } else {
                std::uint8_t event_type = status & 0xF0;
                if (event_type == 0x80 || event_type == 0x90 ||
                    event_type == 0xA0 || event_type == 0xB0 ||
                    event_type == 0xE0)
                    offset += 2;
                else if (event_type == 0xC0 || event_type == 0xD0) offset += 1;
            }
        }
        return 500000; // default 120 BPM if no tempo event found
    }

    float get_bpm(const float tempo_us) {
        return 60000000.0f / tempo_us;
    }

    float get_rate(const float bpm) {
        return bpm / 60.0f;
    }
}
