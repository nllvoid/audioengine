#define SAMPLE_RATE 44100.f
#include "core/Arpeggiator.h"
#include "core/Envelope.h"
#include "core/Oscillator.h"
#include "effects/Delay.h"
#include "effects/EffectChain.h"
#include "effects/HighPassFilter.h"
#include "effects/LowPassFilter.h"
#include "effects/Reverb.h"
#include "effects/SoftClipping.h"
#include "midi/Header.h"
#include "midi/MidiNote.h"
#include "midi/MidiValues.h"
#include "midi/Read.h"
#include "midi/TrackHeader.h"
#include "player/AudioPlayer.h"

int main() {
    auto file = AudioEngine::read_file_data("/Users/yevhenii/Downloads/Vivaldi Spring.mid");
    auto header = AudioEngine::Header::parse_file_header(file);
    AudioEngine::print_header(header);

    if (header.ticks_division & 0x8000)
        throw std::runtime_error("SMPTE timecode division not supported");

    std::size_t offset = 14;

    std::uint32_t tempo_us = AudioEngine::parse_tempo(file, offset);
    float BPM = AudioEngine::get_bpm(static_cast<float>(tempo_us));
    float RATE = AudioEngine::get_rate(BPM);
    float ticks_per_sample = static_cast<float>(header.ticks_division) * BPM / (60.f * SAMPLE_RATE);

    std::printf("Tempo: %.1f BPM → RATE: %.2f notes/sec\n", BPM, RATE);
    std::printf("ticks_per_sample: %.6f\n", ticks_per_sample);

    std::vector<AudioEngine::MidiNote> notes_list;
    for (int i = 0; i < header.tracks_number; i++) {
        auto midi_notes = AudioEngine::parse_track(file, offset, ticks_per_sample);
        std::printf("Track %d: %zu notes\n", i, midi_notes.size());

        if (i == 1) {
            for (const auto& mn : midi_notes) {
                notes_list.push_back(mn);
            }
        }

        AudioEngine::TrackHeader th;
        std::memcpy(&th, file.data() + offset, sizeof(AudioEngine::TrackHeader));
        offset += 8 + __builtin_bswap32(th.length);
    }

    std::printf("Total notes collected: %zu\n", notes_list.size());

auto envelope = AudioEngine::Envelope(SAMPLE_RATE, 0.005f, 0.15f, 0.4f, 0.3f);
    auto oscillator = AudioEngine::Oscillator(
        SAMPLE_RATE, 1,
        notes_list[0].note,
        AudioEngine::WaveType::SINE,
        AudioEngine::PitchModulation::LOGARITHMIC,
        notes_list[0].note,
        0.01f
    );

    auto chain = AudioEngine::EffectChain{
        AudioEngine::LowPassFilter{500.f, SAMPLE_RATE},
        AudioEngine::HighPassFilter{80.f, SAMPLE_RATE},
    };
    oscillator.set_effect_chain(chain);
    oscillator.set_envelope(envelope);
    auto arp    = AudioEngine::Arpeggiator(notes_list, SAMPLE_RATE, oscillator);
    auto player = AudioEngine::AudioPlayer(SAMPLE_RATE, std::move(arp));

    player.play();

    return 0;
}
