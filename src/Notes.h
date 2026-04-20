//
// Created by yevhenii on 20.04.2026.
//

#ifndef NOTES_H
#define NOTES_H

namespace AudioEngine::Notes {
    // Octave 4
    constexpr float C = 261.63f;
    constexpr float Cs = 277.18f;
    constexpr float D = 293.66f;
    constexpr float Ds = 311.13f;
    constexpr float E = 329.63f;
    constexpr float F = 349.23f;
    constexpr float Fs = 369.99f;
    constexpr float G = 392.00f;
    constexpr float Gs = 415.30f;
    constexpr float A = 440.00f;
    constexpr float As = 466.16f;
    constexpr float B = 493.88f;

    constexpr float O0 = 1.0f / 16.0f;
    constexpr float O1 = 1.0f / 8.0f;
    constexpr float O2 = 1.0f / 4.0f;
    constexpr float O3 = 1.0f / 2.0f;
    constexpr float O4 = 1.0f;
    constexpr float O5 = 2.0f;
    constexpr float O6 = 4.0f;
    constexpr float O7 = 8.0f;
    constexpr float O8 = 16.0f;
}

#endif //NOTES_H
