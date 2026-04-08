#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <cmath>

#include "max_int32_audio.h"

namespace RustyAudio
{

// Triangle wave: linear rise from 0 to peak, fall through zero to trough, back to 0.
// Shape per period: 0 -> +1 -> 0 -> -1 -> 0
class WaveformTriangle
{
    static constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9;

    WaveformSinusoid mBase;

public:
    WaveformTriangle(float duration, float amplitude, float frequencyHz) :
        mBase(duration, amplitude, frequencyHz)
    {}

    std::int32_t operator()(float milliseconds) const
    {
        const float phase = std::fmod(mBase.frequency() * milliseconds / 1000.0f, 1.0f);

        float sample;
        if (phase < 0.25f)
            sample = 4.0f * phase;
        else if (phase < 0.75f)
            sample = 2.0f - 4.0f * phase;
        else
            sample = 4.0f * phase - 4.0f;

        return static_cast<std::int32_t>(mBase.amplitude() * MAX_INT32_AS_FLOAT * sample);
    }

    float duration()  const { return mBase.duration(); }
    float amplitude() const { return mBase.amplitude(); }
    float frequency() const { return mBase.frequency(); }
};

}
