#include <iostream>
#include "Oscillator.h"
#include "AudioPlayer.h"
#include "effects/LowPassFilter.h"
#include "../vendor/miniaudio.h"
#include "effects/Delay.h"
#include "effects/HardClipping.h"
#include "effects/HighPassFilter.h"
#include "effects/SoftClipping.h"

#define SAMPLE_RATE 44100.f

int main(int argc, char *argv[]) {
    auto oscillator = AudioEngine::Oscillator(SAMPLE_RATE, 55.f, AudioEngine::WaveType::SQUARE);
    oscillator.add_effect(std::make_unique<AudioEngine::HardClipping>(0.5));
    oscillator.add_effect(std::make_unique<AudioEngine::LowPassFilter>(900.f, SAMPLE_RATE));

    auto player = AudioEngine::AudioPlayer(SAMPLE_RATE, std::move(oscillator));
    player.play();
    return 0;
}
