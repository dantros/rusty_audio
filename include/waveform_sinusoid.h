#pragma once

#include <cstdint>
#include <cmath>
#include <numbers>
#include <limits>
#include <cassert>

namespace RustyAudio
{

class WaveformSinusoid
{
protected:
    // Slight headroom to avoid clipping artifacts at maximum amplitude
    static constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9;

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
        return static_cast<std::int32_t>(MAX_INT32 * sample);
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
