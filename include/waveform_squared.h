#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <limits>

namespace RustyAudio
{

class WaveformSquared
{
    static constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9;

    WaveformSinusoid mBase;

public:
    WaveformSquared(float duration, float amplitude, float frequencyHz) :
        mBase(duration, amplitude, frequencyHz)
    {}

    std::int32_t operator()(float milliseconds) const
    {
        const std::int32_t sinusoidValue = mBase(milliseconds);
        return sinusoidValue > 0 ? MAX_INT32 : -MAX_INT32;
    }

    float duration()  const { return mBase.duration(); }
    float amplitude() const { return mBase.amplitude(); }
    float frequency() const { return mBase.frequency(); }
};

}
