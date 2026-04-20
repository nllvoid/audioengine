#include <iostream>
#include "Oscillator.h"
#include "AudioPlayer.h"
#include "effects/LowPassFilter.h"
#include "../vendor/miniaudio.h"
#include "effects/HighPassFilter.h"


int main(int argc, char *argv[]) {
    auto oscillator = AudioEngine::Oscillator(44100.0f, 440.0f, AudioEngine::WaveType::SINE,
                                                    AudioEngine::PitchModulation::LFO,
                                                    4400.f, 0.00001f,
                                                    440.f, 5.f, 500.f);
    oscillator.add_effect(std::make_unique<AudioEngine::HighPassFilter>(500.f, 44100.f));
    oscillator.add_effect(std::make_unique<AudioEngine::LowPassFilter>(500.f, 44100.f));
    auto player = AudioEngine::AudioPlayer(44100.0f, std::move(oscillator));
    player.play();
    return 0;
}
