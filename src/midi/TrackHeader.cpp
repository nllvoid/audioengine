//
// Created by yevhenii on 02.05.2026.
//
#include "TrackHeader.h"

#include <unordered_map>

#include "MidiNote.h"
#include "VLQ.h"


namespace AudioEngine {
    std::vector<MidiNote> parse_track(const std::vector<std::byte> &file,
                                      std::size_t offset,
                                      const float ticks_per_sample) {
        TrackHeader track_header;
        std::memcpy(&track_header, file.data() + offset, sizeof(TrackHeader));
        track_header.length = __builtin_bswap32(track_header.length);
        offset += sizeof(TrackHeader);

        std::vector<MidiNote> notes;
        std::unordered_map<std::uint8_t, std::pair<uint32_t, std::uint8_t> > active;
        std::uint32_t current_tick = 0;
        const std::size_t end = offset + track_header.length;
        std::uint8_t last_status = 0;

        while (offset < end) {
            const std::uint32_t delta = read_vlq(file, offset);
            current_tick += delta;

            const std::uint8_t byte = std::to_integer<uint8_t>(file[offset]);

            std::uint8_t status;
            if (byte & 0x80) {
                status = byte;
                last_status = status;
                offset++;
            } else {
                status = last_status;
            }

            if (status == 0xFF) {
                const std::uint8_t type = std::to_integer<uint8_t>(file[offset++]);
                const std::uint32_t len = read_vlq(file, offset);
                offset += len;
            } else if (status == 0xF0 || status == 0xF7) {
                const std::uint32_t len = read_vlq(file, offset);
                offset += len;
            } else {
                const std::uint8_t event_type = status & 0xF0;
                const std::uint8_t channel = status & 0x0F;

                if (event_type == 0x80 || event_type == 0x90) {
                    const std::uint8_t note_num = std::to_integer<std::uint8_t>(file[offset++]);
                    const std::uint8_t velocity = std::to_integer<std::uint8_t>(file[offset++]);

                    if (event_type == 0x90 && velocity > 0) {
                        active[note_num] = {current_tick, velocity};
                    } else {
                        if (active.count(note_num)) {
                            auto [tick_on, vel] = active[note_num];
                            notes.push_back({
                                .note = midi_note_to_note(note_num),
                                .tick_on = tick_on,
                                .tick_off = current_tick,
                                .velocity = vel,
                                .channel = channel,
                                .ticks_per_sample = ticks_per_sample
                            });
                            active.erase(note_num);
                        }
                    }
                } else if (event_type == 0xA0 ||
                           event_type == 0xB0 ||
                           event_type == 0xE0) {
                    offset += 2;
                } else if (event_type == 0xC0 ||
                           event_type == 0xD0) {
                    offset += 1;
                }
            }
        }
        return notes;
    }
}
