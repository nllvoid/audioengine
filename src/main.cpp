#include <iostream>
#include "Oscillator.h"
#include "AudioPlayer.h"
#include "../vendor/miniaudio.h"


int main(int argc, char *argv[]) {
    const auto oscillator = AudioEngine::Oscillator(44100.0f, 440.0f, AudioEngine::WaveType::SINE,
                                              AudioEngine::PitchModulation::LFO,
                                              4400.f, 0.00001f,
                                              440.f, 5.f, 500.f);

    auto player = AudioEngine::AudioPlayer(44100.0f, oscillator);
    player.play();
    return 0;
}
