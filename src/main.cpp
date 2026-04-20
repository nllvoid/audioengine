#include <iostream>

#include "Arpeggiator.h"
#include "Oscillator.h"
#include "AudioPlayer.h"
#include "Notes.h"
#include "effects/LowPassFilter.h"
#include "../vendor/miniaudio.h"
#include "effects/Delay.h"
#include "effects/HardClipping.h"
#include "effects/HighPassFilter.h"
#include "effects/SoftClipping.h"

#define SAMPLE_RATE 44100.f

int main() {
    auto oscillator = AudioEngine::Oscillator(
        SAMPLE_RATE, 1,
        AudioEngine::Notes::A * AudioEngine::Notes::O3,
        AudioEngine::WaveType::SINE,
        AudioEngine::PitchModulation::LFO,
        AudioEngine::Notes::A * AudioEngine::Notes::O3,
        0.f,
        0.f,
        0.5f,
        0.8f
    );

    oscillator.add_effect(std::make_unique<AudioEngine::LowPassFilter>(2500.f, SAMPLE_RATE));
    oscillator.add_effect(std::make_unique<AudioEngine::HighPassFilter>(180.f, SAMPLE_RATE));
    oscillator.add_effect(std::make_unique<AudioEngine::Delay>(8820, 0.3f, 0.12f));

    AudioEngine::Arpeggiator arp({
                                     AudioEngine::Notes::A * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::E * AudioEngine::Notes::O4,
                                     AudioEngine::Notes::G * AudioEngine::Notes::O4,
                                     AudioEngine::Notes::C * AudioEngine::Notes::O4,

                                     AudioEngine::Notes::F * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::A * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::E * AudioEngine::Notes::O4,
                                     AudioEngine::Notes::C * AudioEngine::Notes::O4,

                                     AudioEngine::Notes::C * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::G * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::E * AudioEngine::Notes::O4,
                                     AudioEngine::Notes::B * AudioEngine::Notes::O3,

                                     AudioEngine::Notes::G * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::D * AudioEngine::Notes::O4,
                                     AudioEngine::Notes::F * AudioEngine::Notes::O3,
                                     AudioEngine::Notes::B * AudioEngine::Notes::O3,
                                 }, 3.f, SAMPLE_RATE, std::move(oscillator));

    auto player = AudioEngine::AudioPlayer(SAMPLE_RATE, std::move(arp));
    player.play();
    return 0;
}
