#pragma once

#include <cstdint>

#include "max_int32_audio.h"

namespace RustyAudio
{

// White noise: pseudo-random samples generated via a deterministic hash of the
// sample time. No pitch — output is spectrally flat. Useful for percussion, breath,
// or ambient texture.
//
// The hash multiplies milliseconds by 48 to approximate a per-sample index at 48 kHz,
// then applies a MurmurHash3-style finalizer to scatter sequential integers uniformly.
// The result is stateless and reproducible (same time → same value, no mutable state).
class WaveformNoise
{
public:
    WaveformNoise(float duration, float amplitude) :
        mDuration(duration),
        mAmplitude(amplitude)
    {}

    std::int32_t operator()(float milliseconds) const
    {
        uint32_t x = static_cast<uint32_t>(milliseconds * 48.0f);
        x ^= 0x9e3779b9u;
        x = (x ^ (x >> 16)) * 0x45d9f3bu;
        x = (x ^ (x >> 16)) * 0x45d9f3bu;
        x ^= x >> 16;
        const float sample = (float(x) / float(std::numeric_limits<uint32_t>::max())) * 2.0f - 1.0f;
        return static_cast<std::int32_t>(mAmplitude * MAX_INT32_AS_FLOAT * sample);
    }

    float duration()  const { return mDuration; }
    float amplitude() const { return mAmplitude; }

private:
    float mDuration;
    float mAmplitude;
};

}
