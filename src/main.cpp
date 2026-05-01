#include <iostream>

#include "core/Arpeggiator.h"
#include "core/Oscillator.h"
#include "player/AudioPlayer.h"
#include "effects/EffectChain.h"
#include "core/Notes.h"
#include "effects/LowPassFilter.h"
#include "effects/Delay.h"

#define SAMPLE_RATE 44100.f

int main() {
    auto envelope = AudioEngine::Envelope(SAMPLE_RATE, 0.001f, 0.2f, 0.0f, 0.1f);

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
    auto chain = AudioEngine::EffectChain{AudioEngine::LowPassFilter{800.f, SAMPLE_RATE}, AudioEngine::Delay{1000, 0.5, 0.3}};
    envelope.note_on();
    oscillator.set_effect_chain(chain);
    oscillator.set_envelope(envelope);

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
                                 }, 3.f, SAMPLE_RATE, oscillator);

    auto player = AudioEngine::AudioPlayer(SAMPLE_RATE, std::move(arp));
    player.play();
    return 0;
}
