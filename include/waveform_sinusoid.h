#pragma once

#include <cstdint>
#include <cmath>
#include <numbers>
#include <cassert>

#include "max_int32_audio.h"

namespace RustyAudio
{

class WaveformSinusoid
{
public:
    WaveformSinusoid(float duration, float amplitude, float frequencyHz) :
        mDuration(duration),
        mAmplitude(amplitude),
        mFrequencyRadMillis(2 * std::numbers::pi * frequencyHz / 1000)
    {
        assert(0 < amplitude and amplitude <= 1.0);
    }

    std::int32_t operator()(float milliseconds) const
    {
        const float sample = mAmplitude * std::sin(mFrequencyRadMillis * milliseconds);
        return static_cast<std::int32_t>(MAX_INT32_AS_FLOAT * sample);
    }

    float duration() const  { return mDuration; }
    float amplitude() const { return mAmplitude; }
    float frequency() const { return mFrequencyRadMillis * 1000 / (2 * std::numbers::pi); }

private:
    float mDuration;
    float mAmplitude;
    float mFrequencyRadMillis;
};

}
